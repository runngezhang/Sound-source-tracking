/*
 * interface class, inherited from QObject and QGraphicsItem
 * pure virtual class for dot display
 * Need to rewrite setNewDoa
 */
#ifndef INDICATOR_H
#define INDICATOR_H
#include <QObject>
#include <QGraphicsItem>

class indicator : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit indicator(QObject *parent = 0);
    QRectF boundingRect() const;  //bundary condition for painting
    ~indicator();
public:
    virtual void setNewDoa(short newDoa) = 0;  //renew the DOA value

protected:
    //paint function
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

public:
    qreal pointR;  //doa radius
    double doaDegree;  //degree to show
    bool exits;  //if exit?
private:



};

#endif // INDICATOR_H
