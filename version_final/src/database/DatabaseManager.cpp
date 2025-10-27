#include "DatabaseManager.h"
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTextStream>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager inst;
    return inst;
}

DatabaseManager::DatabaseManager()
{
}

bool DatabaseManager::openSQLite()
{
    QString dataDir = QDir::currentPath() + "/data";
    QDir dir;
    if (!dir.exists(dataDir)) dir.mkpath(dataDir);

    QString dbPath = dataDir + "/airline.db";

    m_db = QSqlDatabase::addDatabase("QSQLITE", "qt_sqlite_conn");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qWarning() << "Cannot open SQLite DB:" << m_db.lastError().text();
        return false;
    }

    return initializeSQLiteSchema();
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

bool DatabaseManager::initializeSQLiteSchema()
{
    if (!m_db.isOpen()) return false;

    // If users table exists, assume DB initialized
    if (m_db.tables().contains("users")) return true;

    // If no init.sql is available yet, create minimal schema programmatically
    QSqlQuery q(m_db);
    bool ok = true;

    ok &= q.exec("PRAGMA foreign_keys = ON");
    ok &= q.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "role TEXT NOT NULL)"
    );
    ok &= q.exec(
        "CREATE TABLE IF NOT EXISTS clients ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nom TEXT NOT NULL, "
        "prenom TEXT NOT NULL, "
        "email TEXT, "
        "telephone TEXT)"
    );
    ok &= q.exec(
        "CREATE TABLE IF NOT EXISTS vols ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "code TEXT NOT NULL, "
        "destination TEXT NOT NULL, "
        "date TEXT NOT NULL, "
        "heure TEXT NOT NULL, "
        "compagnie TEXT, "
        "prix REAL DEFAULT 0)"
    );
    ok &= q.exec(
        "CREATE TABLE IF NOT EXISTS reservations ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "client_id INTEGER NOT NULL, "
        "vol_id INTEGER NOT NULL, "
        "date_reservation TEXT NOT NULL, "
        "statut TEXT NOT NULL, "
        "FOREIGN KEY (client_id) REFERENCES clients(id) ON DELETE CASCADE, "
        "FOREIGN KEY (vol_id) REFERENCES vols(id) ON DELETE CASCADE)"
    );

    // Insert demo users if not present
    q.prepare("INSERT OR IGNORE INTO users (username, password, role) VALUES (:u,:p,:r)");
    q.bindValue(":u", "admin"); q.bindValue(":p", "admin123"); q.bindValue(":r", "admin"); q.exec();
    q.bindValue(":u", "user"); q.bindValue(":p", "user123"); q.bindValue(":r", "user"); q.exec();

    // Some sample clients & vols
    q.exec("INSERT OR IGNORE INTO clients (id,nom,prenom,email,telephone) VALUES (1,'Dupont','Jean','jean.dupont@example.com','+33123456789')");
    q.exec("INSERT OR IGNORE INTO clients (id,nom,prenom,email,telephone) VALUES (2,'Martin','Claire','claire.martin@example.com','+33788990011')");
    q.exec("INSERT OR IGNORE INTO vols (id,code,destination,date,heure,compagnie,prix) VALUES (1,'AF123','Paris','2025-11-01','08:30:00','AirFrance',150.0)");
    q.exec("INSERT OR IGNORE INTO vols (id,code,destination,date,heure,compagnie,prix) VALUES (2,'BA456','Londres','2025-11-02','12:00:00','BritishAirways',120.0)");
    q.exec("INSERT OR IGNORE INTO reservations (id,client_id,vol_id,date_reservation,statut) VALUES (1,1,1,'2025-09-30','Confirmée')");

    return ok;
}