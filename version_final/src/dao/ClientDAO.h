#ifndef CLIENTDAO_H
#define CLIENTDAO_H

#include "../models/Client.h"
#include <QList>

class ClientDAO
{
public:
    static QList<Client> all();
    static bool add(const Client &c);
    static bool update(const Client &c);
    static bool remove(int id);
    static QList<Client> search(const QString &term);
    static Client byId(int id);
};

#endif // CLIENTDAO_H