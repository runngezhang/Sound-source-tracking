#include "coordinateIndicator.h"
#include <QPainter>


coordinateIndicator::coordinateIndicator(double length, QObject *parent) :
    indicator(parent)
{
    pointR = 5;
    lineLength = length;

}


void coordinateIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //paint function
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->drawEllipse(QRect(-pointR, -pointR, pointR*2, pointR*2));
}

void coordinateIndicator::setNewDoa(short newDoa)
{
    //renew doa value
    setPos(lineLength*(float)newDoa/360.0f - lineLength/2, -80);
}



