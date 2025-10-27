
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>

class DatabaseManager {
public:

    static DatabaseManager& instance();


    bool openConnection();

    QSqlDatabase getDatabase() const;

private:

    QSqlDatabase db;


    DatabaseManager();
    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
