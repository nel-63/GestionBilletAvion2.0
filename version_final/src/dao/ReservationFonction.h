#ifndef RESERVATIONFONCTION_H
#define RESERVATIONFONCTION_H

#include "../models/Reservation.h"
#include <QList>
#include <QString>

class ReservationFonction
{
public:
    static QList<Reservation> all();
    static bool add(const Reservation &r);
    static bool update(const Reservation &r);
    static bool remove(int id);
    static QList<Reservation> byClientId(int clientId);
    static int count();
    static Reservation byId(int id);
    static QList<Reservation> search(const QString &term);
};

#endif // RESERVATIONFONCTION_H
