#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
    Client() = default;
    int id = -1;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
};

#endif // CLIENT_H