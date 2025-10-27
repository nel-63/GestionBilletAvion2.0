#include "database/DatabaseManager.h"
#include <QSqlError>


DatabaseManager::DatabaseManager() {

    db = QSqlDatabase::addDatabase("QMYSQL", "ma_connexion_principale");
}


DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
    }
}


DatabaseManager& DatabaseManager::instance() {

    static DatabaseManager instance;
    return instance;
}


bool DatabaseManager::openConnection() {


    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("gestion_billet_avion");
    db.setPort(3306);
    db.setPassword("thegoatisback*");

    //  3. Tentative d'ouverture de la connexion
    if (!db.open()) {
        qDebug() << "Échec de la connexion MySQL:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur BDD",
                              "Impossible de se connecter au serveur MySQL. Vérifiez que XAMPP est lancé et que les identifiants sont corrects.");
        return false;
    }

    qDebug() << "Connexion MySQL réussie.";
    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}
