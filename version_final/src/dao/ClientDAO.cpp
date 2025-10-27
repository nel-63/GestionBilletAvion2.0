#include "ClientDAO.h"
#include "database/DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QList<Client> ClientDAO::all()
{
    QList<Client> list;

    QSqlQuery q(DatabaseManager::instance().getDatabase());
    if (!q.exec("SELECT id, nom, prenom, email, telephone FROM clients ORDER BY nom")) {
        qWarning() << q.lastError().text();
        return list;
    }
    // ... (Logique de remplissage de la liste inchangée) ...
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

bool ClientDAO::add(const Client &c)
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

bool ClientDAO::update(const Client &c)
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

bool ClientDAO::remove(int id)
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

QList<Client> ClientDAO::search(const QString &term)
{
    QList<Client> list;
    QSqlQuery q(DatabaseManager::instance().getDatabase());
    q.prepare("SELECT id, nom, prenom, email, telephone FROM clients WHERE nom LIKE :t OR prenom LIKE :t OR email LIKE :t");
    q.bindValue(":t", "%" + term + "%");
    if (!q.exec()) {
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

Client ClientDAO::byId(int id)
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
