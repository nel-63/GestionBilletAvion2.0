#include "ReservationFonction.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

QList<Reservation> ReservationFonction::all()
{
    QList<Reservation> list;

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT id, client_id, vol_id, date_reservation, statut FROM reservations ORDER BY date_reservation DESC")) {
        qWarning() << "ReservationFonction::all ERROR:" << q.lastError().text();
        return list;
    }
    while (q.next()) {
        Reservation r;
        r.id = q.value(0).toInt();
        r.clientId = q.value(1).toInt();
        r.volId = q.value(2).toInt();
        r.dateReservation = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        r.statut = q.value(4).toString();
        list.append(r);
    }
    return list;
}

bool ReservationFonction::add(const Reservation &r)
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("INSERT INTO reservations (client_id, vol_id, date_reservation, statut) VALUES (:c, :v, :d, :s)");
    q.bindValue(":c", r.clientId);
    q.bindValue(":v", r.volId);
    q.bindValue(":d", r.dateReservation.toString(Qt::ISODate));
    q.bindValue(":s", r.statut);
    if (!q.exec()) {
        qWarning() << "ReservationFonction::add ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ReservationFonction::update(const Reservation &r)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("UPDATE reservations SET client_id=:c, vol_id=:v, date_reservation=:d, statut=:s WHERE id=:id");
    q.bindValue(":c", r.clientId);
    q.bindValue(":v", r.volId);
    q.bindValue(":d", r.dateReservation.toString(Qt::ISODate));
    q.bindValue(":s", r.statut);
    q.bindValue(":id", r.id);
    if (!q.exec()) {
        qWarning() << "ReservationFonction::update ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ReservationFonction::remove(int id)
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("DELETE FROM reservations WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qWarning() << "ReservationFonction::remove ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

QList<Reservation> ReservationFonction::byClientId(int clientId)
{
    QList<Reservation> list;

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("SELECT id, client_id, vol_id, date_reservation, statut FROM reservations WHERE client_id=:c ORDER BY date_reservation DESC");
    q.bindValue(":c", clientId);
    if (!q.exec()) {
        qWarning() << "ReservationFonction::byClientId ERROR:" << q.lastError().text();
        return list;
    }
    while (q.next()) {
        Reservation r;
        r.id = q.value(0).toInt();
        r.clientId = q.value(1).toInt();
        r.volId = q.value(2).toInt();
        r.dateReservation = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        r.statut = q.value(4).toString();
        list.append(r);
    }
    return list;
}

int ReservationFonction::count()
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT COUNT(*) FROM reservations")) return 0;
    if (q.next()) return q.value(0).toInt();
    return 0;
}

Reservation ReservationFonction::byId(int id)
{
    Reservation r;
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("SELECT id, client_id, vol_id, date_reservation, statut FROM reservations WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) return r;
    if (q.next()) {
        r.id = q.value(0).toInt();
        r.clientId = q.value(1).toInt();
        r.volId = q.value(2).toInt();
        r.dateReservation = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        r.statut = q.value(4).toString();
    }
    return r;
}

QList<Reservation> ReservationFonction::search(const QString &term)
{
    QList<Reservation> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());

    QString baseQuery =
        "SELECT r.id, r.client_id, r.vol_id, r.date_reservation, r.statut "
        "FROM reservations r "
        "JOIN clients c ON r.client_id = c.id "
        "JOIN vols v ON r.vol_id = v.id";

    if (term.trimmed().isEmpty()) {
        q.prepare(baseQuery);
    }
    else if (term.contains(":")) {
        QStringList parts = term.split(":", Qt::SkipEmptyParts);
        if (parts.size() != 2)
            return list;

        QString field = parts.at(0).trimmed().toLower();
        QString value = parts.at(1).trimmed();

        QString sqlField;
        bool isDate = false;

        if (field == "id") sqlField = "r.id";
        else if (field == "nom") sqlField = "c.nom";
        else if (field == "prenom") sqlField = "c.prenom";
        else if (field == "code") sqlField = "v.code";
        else if (field == "destination") sqlField = "v.destination";
        else if (field == "statut") sqlField = "r.statut";
        else if (field == "date" || field == "date_reservation") { sqlField = "r.date_reservation"; isDate = true; }
        else return list;

        QString filter;

        if (isDate) {
            QString val = value;
            val.replace(" ", "");

            if (val.contains("<")) {
                QStringList range = val.split("<", Qt::SkipEmptyParts);
                if (range.size() == 3 && range.at(1) == field) {
                    QString min = range.at(0);
                    QString max = range.at(2);
                    if (min >= max) return list; // incohérent
                    filter = QString(" WHERE %1 BETWEEN :min AND :max").arg(sqlField);
                    q.prepare(baseQuery + filter);
                    q.bindValue(":min", min);
                    q.bindValue(":max", max);
                }
                else if (range.size() == 2) {
                    QString left = range.at(0);
                    QString right = range.at(1);
                    if (left == field) {
                        filter = QString(" WHERE %1 < :val").arg(sqlField);
                        q.prepare(baseQuery + filter);
                        q.bindValue(":val", right);
                    } else if (right == field) {
                        filter = QString(" WHERE %1 > :val").arg(sqlField);
                        q.prepare(baseQuery + filter);
                        q.bindValue(":val", left);
                    } else return list;
                } else return list;
            } else return list;
        }
        else {
            // recherche texte
            filter = QString(" WHERE %1 LIKE :val").arg(sqlField);
            q.prepare(baseQuery + filter);
            q.bindValue(":val", "%" + value + "%");
        }
    }
    else {
        return list;
    }

    if (!q.exec()) {
        qWarning() << "ReservationFonction::search ERROR:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Reservation r;
        r.id = q.value(0).toInt();
        r.clientId = q.value(1).toInt();
        r.volId = q.value(2).toInt();
        r.dateReservation = QDate::fromString(q.value(3).toString(), Qt::ISODate);
        r.statut = q.value(4).toString();
        list.append(r);
    }

    return list;
}
