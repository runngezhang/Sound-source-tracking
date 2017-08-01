#include "indicator.h"
#include <QPainter>

indicator:: indicator(QObject *parent) :
    QObject(parent)
{
    exits = 0;
    setVisible(false);
    doaDegree = 60.0f/180.0f*M_PI;  //init value set randomly
    pointR = 10;
}
 indicator::~indicator()
{

}

QRectF  indicator::boundingRect() const
{
    qreal adjust = 1;
    return QRectF(-pointR-adjust,-pointR-adjust,pointR*2+adjust*2,pointR*2+adjust*2);
}




