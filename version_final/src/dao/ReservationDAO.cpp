#include "ReservationDAO.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

QList<Reservation> ReservationDAO::all()
{
    QList<Reservation> list;

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT id, client_id, vol_id, date_reservation, statut FROM reservations ORDER BY date_reservation DESC")) {
        qWarning() << "ReservationDAO::all ERROR:" << q.lastError().text();
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

bool ReservationDAO::add(const Reservation &r)
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("INSERT INTO reservations (client_id, vol_id, date_reservation, statut) VALUES (:c, :v, :d, :s)");
    q.bindValue(":c", r.clientId);
    q.bindValue(":v", r.volId);
    q.bindValue(":d", r.dateReservation.toString(Qt::ISODate));
    q.bindValue(":s", r.statut);
    if (!q.exec()) {
        qWarning() << "ReservationDAO::add ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ReservationDAO::update(const Reservation &r)
{
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("UPDATE reservations SET client_id=:c, vol_id=:v, date_reservation=:d, statut=:s WHERE id=:id");
    q.bindValue(":c", r.clientId);
    q.bindValue(":v", r.volId);
    q.bindValue(":d", r.dateReservation.toString(Qt::ISODate));
    q.bindValue(":s", r.statut);
    q.bindValue(":id", r.id);
    if (!q.exec()) {
        qWarning() << "ReservationDAO::update ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

bool ReservationDAO::remove(int id)
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("DELETE FROM reservations WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qWarning() << "ReservationDAO::remove ERROR:" << q.lastError().text();
        return false;
    }
    return true;
}

QList<Reservation> ReservationDAO::byClientId(int clientId)
{
    QList<Reservation> list;

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("SELECT id, client_id, vol_id, date_reservation, statut FROM reservations WHERE client_id=:c ORDER BY date_reservation DESC");
    q.bindValue(":c", clientId);
    if (!q.exec()) {
        qWarning() << "ReservationDAO::byClientId ERROR:" << q.lastError().text();
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

int ReservationDAO::count()
{

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT COUNT(*) FROM reservations")) return 0;
    if (q.next()) return q.value(0).toInt();
    return 0;
}

Reservation ReservationDAO::byId(int id)
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
