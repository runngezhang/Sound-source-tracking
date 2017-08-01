/*
 * class mainWindow: inherited from Qmainwindow to show the GUI
 * containing 4 blocks, 1st block for button groups, 2nd block for DOA display
 * 3rd block for particle display, 4th block for showing previous trace.
 * inititate sub-thread for tracking and use signal and slot to get the new DOA value
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include "circularIndicator.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <trackingthread.h>
#include <vector>
#include <QFile>
#include "coordinateIndicator.h"
#include "particleIndicator.h"
#include "particlePos.h"
#include "pathitem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    //按键组
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *setButton;
    QPushButton *quitButton;
    QPushButton *helpButton;
    QPushButton *aboutButton;

    circularIndicator *indicatorDoa;  //doa indicator on the circle
    coordinateIndicator *cordIndicator;  //doa indicator for the cordinate
    pathItem *pathShow;  //curve to show previous trace
    QGraphicsScene *scene;  //scene group
    QGraphicsScene *scene2;
    QGraphicsScene *scene3;
    QGraphicsEllipseItem *circularShap;  //circle
    QGraphicsLineItem *coordinateDoa;  //coordinate(left-down side)
    QGraphicsLineItem *coordinateDoa2x;  //coordinage(right-down side)
    QGraphicsLineItem *coordinateDoa2y;
    QGraphicsView *view;  //view group
    QGraphicsView *view2;
    QGraphicsView *view3;
    trackingThread *tracking1;  //tracking thread
    double lineLength;  //length of the right-up coordinate
    double lineLength2;  //length of the left-up coordinate
    double lineLength3;
    int numOfLabel;  //num of lables of the axis of the right down side
    int numOfLabel2;  //num of lables of the axis of the right up side
    int numOfLabel3;
    int frameToShow;  //frames/second to show change
    std::vector <QGraphicsTextItem*> *textLabel;  //container for labels for right down side aixs
    std::vector <QGraphicsTextItem*> *textLabel2;  //container for labels for right up side aixs
    std::vector <QGraphicsTextItem*> *textLabel3;
    std::vector <QGraphicsLineItem*> *lineLabel;  //container for line labels for right down side aixs
    std::vector <QGraphicsLineItem*> *lineLabel2;  //container for line labels for right up side aixs
    std::vector <QGraphicsLineItem*> *lineLabel3;
    std::vector <particleIndicator*> *particleIndicatorGroup;  //containers for the particle positions
    particleDoaIndicator *particleDoaIndicator1;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

public slots:
    void startSlot();  //start tracking
    void stopSlot();  //stop
    void updateDoa(short newDoa);  //renew Doa
    void updateParticleShow(particlePos *posGroup);  //renew particle position
    void doaThreadTerminate();  //terminate the thread for tracking

};


#endif // MAINWINDOW_H
