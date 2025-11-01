#ifndef VOLFONCTION_H
#define VOLFONCTION_H

#include "../models/Vol.h"
#include <QList>

class VolFonction
{
public:
    static QList<Vol> all();
    static bool add(const Vol &v);
    static bool update(const Vol &v);
    static bool remove(int id);
    static QList<Vol> search(const QString &term);
    static Vol byId(int id);
    static int count();
};

#endif // VOLFONCTION_H
