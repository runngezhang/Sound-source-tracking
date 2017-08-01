/*
 * inherited from class indicator, show doa on the x-y cordinate
 */
#ifndef COORDINATEINDICATOR_H
#define COORDINATEINDICATOR_H

#include "indicator.h"

class coordinateIndicator : public indicator
{
public:
    explicit coordinateIndicator(double length, QObject *parent = 0);
    void setNewDoa(short newDoa);   //renew DOA

protected:
    //paint function
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    float lineLength;
};

#endif // COORDINATEINDICATOR_H
