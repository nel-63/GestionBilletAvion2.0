#ifndef CONNEXIONSQL_H
#define CONNEXIONSQL_H

#include <QString>
#include <QSqlDatabase>

class ConnexionSQL
{
public:
    static ConnexionSQL& instance();

    // Connecter au serveur MySQL/MariaDB (XAMPP). 
    // host ex: "127.0.0.1" ou "localhost", port ex: 3306
    bool connectMySQL(const QString &host,
                      const QString &user,
                      const QString &password,
                      const QString &database,
                      int port = 3306);

    // Retourne la DB (nommée "qt_mysql_conn")
    QSqlDatabase database() const;

    // Vérifie si la connexion est ouverte
    bool isConnected() const;

    // Exporte le schéma et les données en un fichier SQL (SHOW CREATE TABLE + INSERTs)
    // Renvoie true si succès
    bool exportSchema(const QString &filePath, QString *errorMsg = nullptr);

    // Ferme et déconnecte
    void disconnect();

private:
    ConnexionSQL();
    ~ConnexionSQL();
    ConnexionSQL(const ConnexionSQL&) = delete;
    ConnexionSQL& operator=(const ConnexionSQL&) = delete;

    QSqlDatabase m_db;
    bool m_connected = false;
};

#endif // CONNEXIONSQL_H