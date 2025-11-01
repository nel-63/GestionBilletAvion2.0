#include "VolFonction.h"
#include "../database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QRegularExpression>
#include <QVariantMap>
#include <QStringList>

QList<Vol> VolFonction::all()
{
    QList<Vol> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT id, code, destination, date_vol, heure, compagnie, prix, prix_premiere_class, prix_class_economique FROM vols ORDER BY date_vol, heure")) {
        qWarning() << "VolFonction::all ERROR:" << q.lastError().text();
        return list;
    }
    while (q.next()) {
        Vol v;
        v.id = q.value(0).toInt();
        v.code = q.value(1).toString();
        v.destination = q.value(2).toString();
        v.date = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        v.heure = QTime::fromString(q.value(4).toString(), "HH:mm:ss");
        v.compagnie = q.value(5).toString();
        v.prix = q.value(6).toDouble();
        v.prix_premiere_class = q.value(7).toDouble();
        v.prix_class_economique = q.value(8).toDouble();
        list.append(v);
    }
    return list;
}

bool VolFonction::add(const Vol &v)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("INSERT INTO vols (code, destination, date_vol, heure, compagnie, prix, prix_premiere_class, prix_class_economique) VALUES (:code,:dest,:date_vol,:heure,:comp,:prix,:prix_premiere_class,:prix_class_economique)");
    q.bindValue(":code", v.code);
    q.bindValue(":dest", v.destination);
    q.bindValue(":date_vol", v.date.toString(Qt::ISODate));
    QTime cleanTime(v.heure.hour(), v.heure.minute(), 0);
    q.bindValue(":heure", cleanTime.toString("HH:mm:ss"));
    q.bindValue(":comp", v.compagnie);
    q.bindValue(":prix", v.prix);
    q.bindValue(":prix_premiere_class", v.prix_premiere_class);
    q.bindValue(":prix_class_economique", v.prix_class_economique);
    if (!q.exec()) {
        qWarning() << "VolFonction::add ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool VolFonction::update(const Vol &v)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("UPDATE vols SET code=:code, destination=:dest, date_vol=:date_vol, heure=:heure, compagnie=:comp, prix=:prix, prix_premiere_class=:prix_premiere_class, prix_class_economique=:prix_class_economique WHERE id=:id");
    q.bindValue(":code", v.code);
    q.bindValue(":dest", v.destination);
    q.bindValue(":date_vol", v.date.toString(Qt::ISODate));
    QTime cleanTime(v.heure.hour(), v.heure.minute(), 0);
    q.bindValue(":heure", cleanTime.toString("HH:mm:ss"));
    q.bindValue(":comp", v.compagnie);
    q.bindValue(":prix", v.prix);
    q.bindValue(":prix_premiere_class", v.prix_premiere_class);
    q.bindValue(":prix_class_economique", v.prix_class_economique);
    q.bindValue(":id", v.id);
    if (!q.exec()) {
        qWarning() << "VolFonction::update ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool VolFonction::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("DELETE FROM vols WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qWarning() << "VolFonction::remove ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

QList<Vol> VolFonction::search(const QString &term)
{
    QList<Vol> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());

    QString baseQuery =
        "SELECT id, code, destination, date_vol, heure, compagnie, prix, "
        "prix_premiere_class, prix_class_economique FROM vols";

    QString sql = baseQuery;
    QStringList whereClauses;
    QVariantMap boundValues;
    int placeholderCount = 0;

    if (term.trimmed().isEmpty()) {
        q.prepare(sql);
    } else {
        QRegularExpression re("(\\w+):(\"([^\"]*)\"|'([^']*)'|([^\\s]+))");
        QRegularExpressionMatchIterator it = re.globalMatch(term);

        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString field = match.captured(1).trimmed().toLower();
            QString value = match.captured(3);
            if (value.isEmpty()) value = match.captured(4);
            if (value.isEmpty()) value = match.captured(5);
            value = value.trimmed();

            QString sqlField;
            bool isComparable = false;
            bool isDate = false;

            if (field == "id") { sqlField = "id"; isComparable = true; }
            else if (field == "code") sqlField = "code";
            else if (field == "destination") sqlField = "destination";
            else if (field == "date" || field == "date_vol") { sqlField = "date_vol"; isDate = true; isComparable = true; }
            else if (field == "heure") { sqlField = "heure"; isComparable = true; }
            else if (field == "compagnie") sqlField = "compagnie";
            else if (field == "prix") { sqlField = "prix"; isComparable = true; }
            else if (field == "prix_premiere_class") { sqlField = "prix_premiere_class"; isComparable = true; }
            else if (field == "prix_class_economique") { sqlField = "prix_class_economique"; isComparable = true; }
            else continue;

            placeholderCount++;
            QString minPh = ":min" + QString::number(placeholderCount);
            QString maxPh = ":max" + QString::number(placeholderCount);
            QString valPh = ":val" + QString::number(placeholderCount);

            if (isComparable) {
                QString comparableValue = value;
                comparableValue.replace(" ", "");
                int count = comparableValue.count("<");

                if (field == "heure") {
                    auto parseTime = [](const QString &s) -> QTime {
                        QStringList formats = {"HH:mm:ss", "H:mm:ss", "HH:mm", "H:mm"};
                        for (const auto &f : formats) {
                            QTime t = QTime::fromString(s.trimmed(), f);
                            if (t.isValid()) return t;
                        }
                        return QTime();
                    };

                    QTime minTime, maxTime;

                    if (count == 2) {
                        QStringList parts2 = comparableValue.split("<", Qt::SkipEmptyParts);
                        if (parts2.size() == 3) {
                            QString leftStr = parts2.at(0).trimmed();
                            QString mid = parts2.at(1).trimmed();
                            QString rightStr = parts2.at(2).trimmed();
                            if (mid != field) return list;
                            minTime = parseTime(leftStr);
                            maxTime = parseTime(rightStr);
                            if (!minTime.isValid() || !maxTime.isValid() || minTime >= maxTime) return list;
                            whereClauses.append(QString("%1 BETWEEN %2 AND %3").arg(sqlField, minPh, maxPh));
                            boundValues.insert(minPh, minTime);
                            boundValues.insert(maxPh, maxTime);
                        }
                    }
                    else if (count == 1 && comparableValue.startsWith(field + "<")) {
                        QString valStr = comparableValue.section("<", 1).trimmed();
                        QTime valTime = parseTime(valStr);
                        if (!valTime.isValid()) return list;
                        whereClauses.append(QString("%1 < %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, valTime);
                    }
                    else if (count == 1 && comparableValue.endsWith("<" + field)) {
                        QString valStr = comparableValue.section("<", 0, 0).trimmed();
                        QTime valTime = parseTime(valStr);
                        if (!valTime.isValid()) return list;
                        whereClauses.append(QString("%1 > %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, valTime);
                    }
                    else if (count == 0) {
                        QString valStr = comparableValue.trimmed();
                        QTime valTime = parseTime(valStr);
                        if (!valTime.isValid()) return list;
                        whereClauses.append(QString("%1 = %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, valTime);
                    }
                }
                else if (isDate) {
                    if (count == 2) {
                        QStringList parts2 = comparableValue.split("<", Qt::SkipEmptyParts);
                        if (parts2.size() == 3) {
                            QString leftStr = parts2.at(0).trimmed();
                            QString mid = parts2.at(1).trimmed();
                            QString rightStr = parts2.at(2).trimmed();
                            if (mid != field) continue;
                            whereClauses.append(QString("%1 BETWEEN %2 AND %3").arg(sqlField, minPh, maxPh));
                            QDate minDate = QDate::fromString(leftStr, Qt::ISODate);
                            QDate maxDate = QDate::fromString(rightStr, Qt::ISODate);
                            if (!minDate.isValid() || !maxDate.isValid() || minDate >= maxDate) return list;
                            boundValues.insert(minPh, minDate);
                            boundValues.insert(maxPh, maxDate);
                        }
                    } else if (count == 1 && comparableValue.startsWith(field + "<")) {
                        QString valStr = comparableValue.section("<", 1).trimmed();
                        QDate valDate = QDate::fromString(valStr, Qt::ISODate);
                        if (!valDate.isValid()) continue;
                        whereClauses.append(QString("%1 < %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, valDate);
                    } else if (count == 1 && comparableValue.endsWith("<" + field)) {
                        QString valStr = comparableValue.section("<", 0, 0).trimmed();
                        QDate valDate = QDate::fromString(valStr, Qt::ISODate);
                        if (!valDate.isValid()) continue;
                        whereClauses.append(QString("%1 > %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, valDate);
                    } else if (count == 0) {
                        QString valStr = comparableValue.trimmed();
                        QDate valDate = QDate::fromString(valStr, Qt::ISODate);
                        if (!valDate.isValid()) continue;
                        whereClauses.append(QString("%1 = %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, valDate);
                    }
                }
                else {
                    if (count == 2) {
                        QStringList parts2 = comparableValue.split("<", Qt::SkipEmptyParts);
                        if (parts2.size() == 3) {
                            QString leftStr = parts2.at(0).trimmed();
                            QString mid = parts2.at(1).trimmed();
                            QString rightStr = parts2.at(2).trimmed();
                            if (mid != field) continue;
                            whereClauses.append(QString("%1 BETWEEN %2 AND %3").arg(sqlField, minPh, maxPh));
                            bool okMin, okMax;
                            double minVal = leftStr.toDouble(&okMin);
                            double maxVal = rightStr.toDouble(&okMax);
                            if (!okMin || !okMax || minVal >= maxVal) return list;
                            boundValues.insert(minPh, minVal);
                            boundValues.insert(maxPh, maxVal);
                        }
                    } else if (count == 1 && comparableValue.startsWith(field + "<")) {
                        QString valStr = comparableValue.section("<", 1).trimmed();
                        bool ok; double val = valStr.toDouble(&ok); if (!ok) continue;
                        whereClauses.append(QString("%1 < %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, val);
                    } else if (count == 1 && comparableValue.endsWith("<" + field)) {
                        QString valStr = comparableValue.section("<", 0, 0).trimmed();
                        bool ok; double val = valStr.toDouble(&ok); if (!ok) continue;
                        whereClauses.append(QString("%1 > %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, val);
                    } else if (count == 0) {
                        QString valStr = comparableValue.trimmed();
                        bool ok; double val = valStr.toDouble(&ok); if (!ok) continue;
                        whereClauses.append(QString("%1 = %2").arg(sqlField, valPh));
                        boundValues.insert(valPh, val);
                    }
                }
            }
            else {
                whereClauses.append(QString("%1 LIKE %2").arg(sqlField, valPh));
                boundValues.insert(valPh, "%" + value + "%");
            }
        }

        if (!whereClauses.isEmpty()) sql += " WHERE " + whereClauses.join(" AND ");
        q.prepare(sql);
        for (auto it = boundValues.constBegin(); it != boundValues.constEnd(); ++it) q.bindValue(it.key(), it.value());
    }

    if (!q.exec()) {
        qWarning() << "VolFonction::search ERROR:" << q.lastError().text();
        qWarning() << "Query:" << q.lastQuery();
        return list;
    }

    while (q.next()) {
        Vol v;
        v.id = q.value(0).toInt();
        v.code = q.value(1).toString();
        v.destination = q.value(2).toString();
        v.date = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        v.heure = QTime::fromString(q.value(4).toString(), "HH:mm:ss");
        v.compagnie = q.value(5).toString();
        v.prix = q.value(6).toDouble();
        v.prix_premiere_class = q.value(7).toDouble();
        v.prix_class_economique = q.value(8).toDouble();
        list.append(v);
    }

    return list;
}



Vol VolFonction::byId(int id)
{
    Vol v;
    QSqlQuery q(DatabaseManager::instance().getDatabase());

    q.prepare("SELECT id, code, destination, date_vol, heure, compagnie, prix, prix_premiere_class, prix_class_economique FROM vols WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) return v;
    if (q.next()) {
        v.id = q.value(0).toInt();
        v.code = q.value(1).toString();
        v.destination = q.value(2).toString();
        v.date = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        v.heure = QTime::fromString(q.value(4).toString(), "HH:mm:ss");
        v.compagnie = q.value(5).toString();
        v.prix = q.value(6).toDouble();
        v.prix_premiere_class = q.value(7).toDouble();
        v.prix_class_economique = q.value(8).toDouble();
    }
    return v;
}

int VolFonction::count()
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT COUNT(*) FROM vols")) return 0;
    if (q.next()) return q.value(0).toInt();
    return 0;
}
