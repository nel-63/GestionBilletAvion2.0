#include "ClientFonction.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>
#include <QVariantMap>
#include <QRegularExpression>

QList<Client> ClientFonction::all()
{
    QList<Client> list;

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT id, nom, prenom, email, telephone FROM clients ORDER BY nom")) {
        qWarning() << q.lastError().text();
        return list;
    }

    while (q.next()) {
        Client c;
        c.id = q.value(0).toInt();
        c.nom = q.value(1).toString();
        c.prenom = q.value(2).toString();
        c.email = q.value(3).toString();
        c.telephone = q.value(4).toString();
        list.append(c);
    }
    return list;
}

bool ClientFonction::add(const Client &c)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("INSERT INTO clients (nom, prenom, email, telephone) VALUES (:n, :p, :e, :t)");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":e", c.email);
    q.bindValue(":t", c.telephone);
    if (!q.exec()) {
        qWarning() << q.lastError().text();
        return false;
    }
    return true;
}

bool ClientFonction::update(const Client &c)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("UPDATE clients SET nom=:n, prenom=:p, email=:e, telephone=:t WHERE id=:id");
    q.bindValue(":n", c.nom);
    q.bindValue(":p", c.prenom);
    q.bindValue(":e", c.email);
    q.bindValue(":t", c.telephone);
    q.bindValue(":id", c.id);
    if (!q.exec()) {
        qWarning() << q.lastError().text();
        return false;
    }
    return true;
}

bool ClientFonction::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("DELETE FROM clients WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qWarning() << q.lastError().text();
        return false;
    }
    return true;
}

QList<Client> ClientFonction::search(const QString &term)
{
    QList<Client> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());

    QString trimmedTerm = term.trimmed();
    QString baseQuery = "SELECT id, nom, prenom, email, telephone FROM clients";
    QStringList whereClauses;
    QVariantMap boundValues;
    int placeholderCount = 0;

    if (trimmedTerm.isEmpty()) {
        q.prepare(baseQuery);
    }
    else {

        QRegularExpression re("(\\w+):(\"([^\"]*)\"|'([^']*)'|([^\\s]+))");
        QRegularExpressionMatchIterator it = re.globalMatch(trimmedTerm);

        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();

            QString field = match.captured(1).trimmed().toLower();
            QString value = match.captured(3);
            if (value.isEmpty()) value = match.captured(4);
            if (value.isEmpty()) value = match.captured(5);

            value = value.trimmed();

            QString sqlField;

            if (field == "id") sqlField = "id";
            else if (field == "nom") sqlField = "nom";
            else if (field == "prenom") sqlField = "prenom";
            else if (field == "email") sqlField = "email";
            else if (field == "telephone") sqlField = "telephone";
            else continue;

            placeholderCount++;
            QString valPh = ":val" + QString::number(placeholderCount);

            whereClauses.append(QString("%1 LIKE %2").arg(sqlField, valPh));
            boundValues.insert(valPh, "%" + value + "%");
        }


        if (!whereClauses.isEmpty()) {
            q.prepare(baseQuery + " WHERE " + whereClauses.join(" AND "));

            for (auto mapIt = boundValues.constBegin(); mapIt != boundValues.constEnd(); ++mapIt) {
                q.bindValue(mapIt.key(), mapIt.value());
            }
        }
    }
    if (q.lastQuery().isEmpty()) {
        return list;
    }

    if (!q.exec()) {
        qWarning() << "ClientFonction::search ERROR:" << q.lastError().text();
        qWarning() << "Query:" << q.lastQuery();
        return list;
    }

    while (q.next()) {
        Client c;
        c.id = q.value(0).toInt();
        c.nom = q.value(1).toString();
        c.prenom = q.value(2).toString();
        c.email = q.value(3).toString();
        c.telephone = q.value(4).toString();
        list.append(c);
    }
    return list;
}

Client ClientFonction::byId(int id)
{
    Client c;
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("SELECT id, nom, prenom, email, telephone FROM clients WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) return c;
    if (q.next()) {
        c.id = q.value(0).toInt();
        c.nom = q.value(1).toString();
        c.prenom = q.value(2).toString();
        c.email = q.value(3).toString();
        c.telephone = q.value(4).toString();
    }
    return c;
}
