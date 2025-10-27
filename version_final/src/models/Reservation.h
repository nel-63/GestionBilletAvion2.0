#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>

class Reservation
{
public:
    Reservation() = default;
    int id = -1;
    int clientId = -1;
    int volId = -1;
    QDate dateReservation;
    QString statut;
};

#endif // RESERVATION_H
