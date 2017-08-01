#include "particleIndicator.h"
#include <QPainter>


particleIndicator::particleIndicator(double length, QObject *parent) :
    indicator(parent)
{
    lineLength = length;
    pointR = 1;

}



void particleIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->drawEllipse(QRect(-pointR, -pointR, pointR*2, pointR*2));
}

void particleIndicator::setNewDoa(short newDoa)
{
    setPos(lineLength*(float)newDoa/360.0f - lineLength/2, -20);
}


particleDoaIndicator::particleDoaIndicator(double length, QObject *parent) :
    indicator(parent)
{
    lineLength = length;
    pointR = 10;

}

//paint function
void particleDoaIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::red);
    painter->setBrush(Qt::red);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->drawEllipse(QRect(-pointR, -pointR, pointR*2, pointR*2));
}

//renew the DOA value
void particleDoaIndicator::setNewDoa(short newDoa)
{
    setPos(lineLength*(float)newDoa/360.0f - lineLength/2, -35);
}


