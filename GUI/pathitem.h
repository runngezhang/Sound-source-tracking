/*
 * class doaPoint: points in the path line,inlcude doa and if the point is visible
 * class pathItem: inherited from QObject and QGraphicsItem
 *                 manage the path line and draw it
 */
#ifndef PATHITEM_H
#define PATHITEM_H
#include <QObject>
#include <QGraphicsItem>
#include <list>

class doaPoint
{
public:
    bool state;  //if visible
    short doa;  //current doa
public:
    doaPoint();
    doaPoint(short newDoa, bool newState);
    ~doaPoint();
};


class pathItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    pathItem(float inWidth, float inHeight, int inFramesToShow, QObject *parent = 0);
    QRectF boundingRect() const;  //boundary info
    ~pathItem();
public:
    void setNewDoa(short newDoa, bool newState);  //renew Doa
protected:
    //paint function
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    float width;  //width for painting
    float height;  //height for painting
    int framesToShow;  //total frames to show
    std::list<doaPoint> *doaBuffer;  //path line consist of the dots
private:


};


#endif // PATHITEM_H
