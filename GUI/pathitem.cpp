#include "pathitem.h"
#include <Qpainter>

pathItem:: pathItem(float inWidth, float inHeight, int inFramesToShow, QObject *parent):
    QObject(parent)
{
    width = inWidth;
    height = inHeight;
    framesToShow = inFramesToShow;
    doaBuffer = new std::list<doaPoint> (framesToShow);
}
 pathItem::~pathItem()
{
    delete doaBuffer;
    doaBuffer = NULL;
}

QRectF  pathItem::boundingRect() const
{
    return QRectF(-width/2,-height/2,width,height);
}

//paint function
void pathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //set color and stroke
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);
    painter->setBrush(Qt::red);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing,true);

    //draw lines connecting adjecent dots
    std::list<doaPoint>::iterator firstIter = (*doaBuffer).begin();
    std::list<doaPoint>::iterator nextIter = (*doaBuffer).begin();
    nextIter++;
    float temp1 = 1.0f / (float)(framesToShow-1);
    float temp2 = 1.0f / 360.0f;
    int i = 0;
    for(; nextIter != (*doaBuffer).end(); )
    {
        //draw line if the adjecent dots are both visible
        if((firstIter->state == true) && (nextIter->state == true))
        {
            float startx = (float)i * temp1
                    * (float)width - (float)width/2;
            float starty = - (float)firstIter->doa * temp2
                     * (float)height + (float)height/2;
            QPoint startPoint(startx, starty);
            float endx = (float)(i+1) *temp1
                    * (float)width - (float)width/2;
            float endy = - (float)nextIter->doa * temp2
                    * (float)height + (float)height/2;
            QPoint endPoint(endx, endy);
            //prevent drawing lines from 0 degree to 360 degree
            if(abs(firstIter->doa - nextIter->doa) < 300)
            {
                 painter->drawLine(startPoint, endPoint);
            }
        }

        firstIter++; nextIter++; i++;
    }
}

//renew doa
void pathItem::setNewDoa(short newDoa, bool newState)
{
    doaBuffer->erase(doaBuffer->begin());
    doaPoint newPoint(newDoa, newState);
    doaBuffer->push_back(newPoint);
    newState = newState;
    update();
}

doaPoint::doaPoint()
{
    state = false;
    doa = 0;
}

doaPoint::doaPoint(short newDoa, bool newState)
{
    state = newState;
    doa = newDoa;
}

doaPoint::~doaPoint()
{

}
