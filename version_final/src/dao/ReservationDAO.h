#ifndef RESERVATIONDAO_H
#define RESERVATIONDAO_H

#include "../models/Reservation.h"
#include <QList>
#include <QString> // Ajouté pour s'assurer que QList<QString> est bien défini

class ReservationDAO
{
public:
    static QList<Reservation> all();
    static bool add(const Reservation &r);
    static bool update(const Reservation &r);
    static bool remove(int id);
    static QList<Reservation> byClientId(int clientId);
    static int count();
    static Reservation byId(int id);
};

#endif // RESERVATIONDAO_H
