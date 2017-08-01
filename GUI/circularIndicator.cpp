#include "circularIndicator.h"
#include <QPainter>

circularIndicator::circularIndicator(QObject *parent) :
    indicator(parent)
{
    radius = 100;

}


void circularIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //paint function
    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->drawEllipse(QRect(-pointR, -pointR, pointR*2, pointR*2));
}


void circularIndicator::setNewDoa(short newDoa)
{
    //renew the DOA
    doaDegree = (float)newDoa/180.0f*M_PI;
    setPos(-radius*sin(doaDegree), radius*cos(doaDegree));
}

