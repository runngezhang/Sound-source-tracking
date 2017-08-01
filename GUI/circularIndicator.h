/*
 * inherited from indicator, indicate the DOA result on the circle
 */

#ifndef INDICATORCICULAR_H
#define INDICATORCICULAR_H

#include "indicator.h"

class circularIndicator : public indicator
{
public:
    explicit circularIndicator(QObject *parent = 0);
    void setNewDoa(short newDoa);    //renew the DOA value

protected:
    //plot the dot
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    float radius;
};

#endif // INDICATORCICULAR_H
