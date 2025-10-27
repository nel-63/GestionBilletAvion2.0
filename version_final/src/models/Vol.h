#ifndef VOL_H
#define VOL_H

#include <QString>
#include <QDate>
#include <QTime>

class Vol
{
public:
    Vol() = default;
    int id = -1;
    QString code;
    QString destination;
    QDate date;
    QTime heure;
    QString compagnie;
    double prix = 0.0;
    double prix_premiere_class = 0.0;
    double prix_class_economique = 0.0;

};

#endif // VOL_H
