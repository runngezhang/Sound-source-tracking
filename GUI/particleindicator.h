/*
 * inherited from indicator,show particles
 */

#ifndef PARTICLEINDICATOR_H
#define PARTICLEINDICATOR_H


#include "indicator.h"

class particleIndicator : public indicator
{
public:
    explicit particleIndicator(double length, QObject *parent = 0);
    void setNewDoa(short newDoa);  //renewal

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    float lineLength;
};


class particleDoaIndicator : public indicator
{
public:
    explicit particleDoaIndicator(double length, QObject *parent = 0);
    void setNewDoa(short newDoa);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    float lineLength;
};


#endif // PARTICLEINDICATOR_H
