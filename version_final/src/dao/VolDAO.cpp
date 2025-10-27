#include "VolDAO.h"
#include "../database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>

QList<Vol> VolDAO::all()
{
    QList<Vol> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT id, code, destination, date_vol, heure, compagnie, prix, prix_premiere_class, prix_class_economique FROM vols ORDER BY date_vol, heure")) {
        qWarning() << "VolDAO::all ERROR:" << q.lastError().text();
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

bool VolDAO::add(const Vol &v)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("INSERT INTO vols (code, destination, date_vol, heure, compagnie, prix, prix_premiere_class, prix_class_economique) VALUES (:code,:dest,:date_vol,:heure,:comp,:prix,:prix_premiere_class,:prix_class_economique)");
    q.bindValue(":code", v.code);
    q.bindValue(":dest", v.destination);
    q.bindValue(":date_vol", v.date.toString(Qt::ISODate));
    q.bindValue(":heure", v.heure.toString("HH:mm:ss"));
    q.bindValue(":comp", v.compagnie);
    q.bindValue(":prix", v.prix);
    q.bindValue(":prix_premiere_class", v.prix_premiere_class);
    q.bindValue(":prix_class_economique", v.prix_class_economique);
    if (!q.exec()) {
        qWarning() << "VolDAO::add ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool VolDAO::update(const Vol &v)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("UPDATE vols SET code=:code, destination=:dest, date_vol=:date_vol, heure=:heure, compagnie=:comp, prix=:prix, prix_première_class=:prix_premiere_class, prix_class_economique=:prix_class_economique WHERE id=:id");
    q.bindValue(":code", v.code);
    q.bindValue(":dest", v.destination);
    q.bindValue(":date_vol", v.date.toString(Qt::ISODate));
    q.bindValue(":heure", v.heure.toString("HH:mm:ss"));
    q.bindValue(":comp", v.compagnie);
    q.bindValue(":prix", v.prix);
    q.bindValue(":prix_premiere_class", v.prix_premiere_class);
    q.bindValue(":prix_class_economique", v.prix_class_economique);
    q.bindValue(":id", v.id);
    if (!q.exec()) {
        qWarning() << "VolDAO::update ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool VolDAO::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("DELETE FROM vols WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qWarning() << "VolDAO::remove ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

QList<Vol> VolDAO::search(const QString &term)
{
    QList<Vol> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("SELECT id, code, destination, date_vol, heure, compagnie, prix, prix_premiere_class, prix_class_economique FROM vols WHERE code LIKE :t OR destination LIKE :t OR compagnie LIKE :t");
    q.bindValue(":t", "%" + term + "%");
    if (!q.exec()) {
        qWarning() << "VolDAO::search ERROR:" << q.lastError().text();
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

Vol VolDAO::byId(int id)
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

int VolDAO::count()
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT COUNT(*) FROM vols")) return 0;
    if (q.next()) return q.value(0).toInt();
    return 0;
}
