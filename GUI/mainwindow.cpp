#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFont>
#include <trackingthread.h>
#include <QString>
#include <unistd.h>
#include "stdafx.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //reading qss file defining the button style
    QFile file(":/new/prefix1/pushButtonMetro.qss");
    file.open(QFile::ReadOnly);
    QString stylesheetMetro = tr(file.readAll());

    QFile fileStart(":/new/prefix1/pushButtonStart.qss");
    fileStart.open(QFile::ReadOnly);
    QString stylesheetStart = tr(fileStart.readAll());

    QFile fileStop(":/new/prefix1/pushButtonStop.qss");
    fileStop.open(QFile::ReadOnly);
    QString stylesheetStop = tr(fileStop.readAll());


    //setting the property of the window
    this->setStyleSheet("background-color: rgb(70,70,70)");
    this->setWindowFlags(Qt::FramelessWindowHint);
    setMaximumSize(1000, 600);
    setMinimumSize(1000, 600);


    //plot push button group
    startButton = new QPushButton(this);
    startButton->setStyleSheet(stylesheetStart);
    startButton->setGeometry(QRect(350, 520, 70, 70));
    startButton->setFlat(true);

    stopButton = new QPushButton(this);
    stopButton->setStyleSheet(stylesheetStop);
    stopButton->setGeometry(QRect(500, 520, 70, 70));
    stopButton->setFlat(true);

    helpButton = new QPushButton("  Help", this);
    helpButton->setStyleSheet(stylesheetMetro);
    helpButton->setGeometry(QRect(40, 20, 200, 40));

    aboutButton = new QPushButton("  About", this);
    aboutButton->setGeometry(QRect(40, 65, 200, 40));
    aboutButton->setStyleSheet(stylesheetMetro);

    setButton = new QPushButton("  Settings", this);
    setButton->setGeometry(QRect(40, 110, 200, 40));
    setButton->setStyleSheet(stylesheetMetro);

    quitButton = new QPushButton("  Quit", this);
    quitButton->setGeometry(QRect(40, 155, 200, 40));
    quitButton->setStyleSheet(stylesheetMetro);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));


    /*
     *scene 1，circular Doa display, show the sound source relative angle. Containing relavent GraphicsView
     * and a circle and the indicator
     */

    scene = new QGraphicsScene;
    scene->setSceneRect(-150, -150, 300, 300);
    QPen pen1;
    pen1.setWidth(5);
    pen1.setBrush(Qt::white);
    double radius = 100;

    //circle
    circularShap = new QGraphicsEllipseItem(QRect(-radius, -radius, radius*2, radius*2));
    circularShap->setPen(pen1);

    //Doa indicator
    indicatorDoa = new circularIndicator;
    indicatorDoa->setParentItem(circularShap);
    scene->addItem(circularShap);

    view = new QGraphicsView;
    view->setScene(scene);
    view->setParent(this);
    view->setGeometry(QRect(40, 220, 300, 300));
    view->setFrameStyle(0);
    view->setStyleSheet("background-color: rgb(85, 170, 255)");
    view->show();


    /*
     * scene 2, for particle position display. Including buffer, axis, axis labels
     * particle positions and the DOA estimation results using particle filtering
     */
    scene2 = new QGraphicsScene;
    scene2->setSceneRect(-300, -100, 600, 200);
    QPen pen2;
    pen2.setWidth(4);
    pen2.setBrush(Qt::white);

    //axis
    lineLength = 500;
    coordinateDoa = new QGraphicsLineItem(-lineLength/2, 0, lineLength/2, 0);
    coordinateDoa->setPen(pen2);
    scene2->addItem(coordinateDoa);

    //plot labels
    numOfLabel = 10;
    textLabel = new std::vector <QGraphicsTextItem*> (numOfLabel);
    lineLabel = new std::vector <QGraphicsLineItem*> (numOfLabel);
    for(int i = 0; i < numOfLabel; i++)
    {
        short temp = (float)i / (float)(numOfLabel-1) * (float)lineLength - (float)lineLength/2;
        (*textLabel)[i] = new QGraphicsTextItem;
        (*lineLabel)[i] = new QGraphicsLineItem(0, 0, 0, 2);
        (*lineLabel)[i]->setPen(pen2);

        (*lineLabel)[i]->setPos(temp, 0);
        (*lineLabel)[i]->setParentItem(coordinateDoa);
        (*textLabel)[i]->setPlainText(QString::number(i*(float)(360)/(numOfLabel-1)));
        (*textLabel)[i]->setFont(QFont("Times", 18, QFont::Bold));
        (*textLabel)[i]->setParentItem(coordinateDoa);
        (*textLabel)[i]->setDefaultTextColor(QColor("white"));
        (*textLabel)[i]->setPos(temp-(*textLabel)[i]->boundingRect().width()/2, 0);
    }

    //Original noisy DOA observation results
    cordIndicator = new coordinateIndicator(lineLength);
    cordIndicator->setParentItem(coordinateDoa);

    //DOA after particle filtering
    particleDoaIndicator1 = new particleDoaIndicator(lineLength);
    particleDoaIndicator1->setParentItem(coordinateDoa);

    //particle positions
    particleIndicatorGroup = new std::vector<particleIndicator*>(numParticle);
    for(int i = 0; i < numParticle; i++)
    {
       (*particleIndicatorGroup)[i] = new particleIndicator(lineLength);
       (*particleIndicatorGroup)[i]->setParentItem(coordinateDoa);
    }

    view2 = new QGraphicsView;
    view2->setStyleSheet("background-color: rgb(85, 170, 255)");
    view2->setScene(scene2);
    view2->setParent(this);
    view2->setGeometry(QRect(350, 320, 600, 200));
    view2->setFrameStyle(0);
    view2->show();


    /*
     * scene 3 to show previous trace. Including buffer, 2 axis and their labels,
     * and previous trace.
     */
    scene3 = new QGraphicsScene;
    scene3->setSceneRect(-300, -140, 600, 280);

    //plot axis
    lineLength2 = 400;
    lineLength3 = 200;
    coordinateDoa2x = new QGraphicsLineItem(-lineLength2/2, lineLength3/2,
                                            lineLength2/2, lineLength3/2);

    numOfLabel2 = 8;
    frameToShow = 200;
    textLabel2 = new std::vector <QGraphicsTextItem*> (numOfLabel);
    lineLabel2 = new std::vector <QGraphicsLineItem*> (numOfLabel);
    for(int i = 0; i < numOfLabel2; i++)
    {
        short temp = (float)i / (float)(numOfLabel2-1) * (float)lineLength2 - (float)lineLength2/2;
        (*textLabel2)[i] = new QGraphicsTextItem;
        (*lineLabel2)[i] = new QGraphicsLineItem(0, 0, 0, 2);
        (*lineLabel2)[i]->setPen(pen2);

        (*lineLabel2)[i]->setPos(temp, lineLength3/2);
        (*lineLabel2)[i]->setParentItem(coordinateDoa2x);
        (*textLabel2)[i]->setPlainText(QString::number((int)(i*(float)(frameToShow)/(numOfLabel2-1))));
        (*textLabel2)[i]->setFont(QFont("Times", 15, QFont::Bold));
        (*textLabel2)[i]->setParentItem(coordinateDoa2x);
        (*textLabel2)[i]->setDefaultTextColor(QColor("white"));
        (*textLabel2)[i]->setPos(temp-(*textLabel2)[i]->boundingRect().width()/2, lineLength3/2);
    }
    coordinateDoa2x->setPen(pen2);
    scene3->addItem(coordinateDoa2x);


    coordinateDoa2y = new QGraphicsLineItem(-lineLength2/2, -lineLength3/2,
                                            -lineLength2/2, lineLength3/2);
    coordinateDoa2y->setPen(pen2);
    scene3->addItem(coordinateDoa2y);

    numOfLabel3 = 9;
    textLabel3 = new std::vector <QGraphicsTextItem*> (numOfLabel);
    lineLabel3 = new std::vector <QGraphicsLineItem*> (numOfLabel);
    for(int i = 0; i < numOfLabel3; i++)
    {
        short temp = (float)i / (float)(numOfLabel3-1) * (float)lineLength3 - (float)lineLength3/2;
        (*textLabel3)[i] = new QGraphicsTextItem;
        (*lineLabel3)[i] = new QGraphicsLineItem(0, 0, -2, 0);
        (*lineLabel3)[i]->setPen(pen2);

        (*lineLabel3)[i]->setPos(-lineLength2/2, temp);
        (*lineLabel3)[i]->setParentItem(coordinateDoa2y);
        (*textLabel3)[i]->setPlainText(QString::number((int)(i*(float)(360)/(numOfLabel3-1))));
        (*textLabel3)[i]->setFont(QFont("Times", 15, QFont::Bold));
        (*textLabel3)[i]->setParentItem(coordinateDoa2y);
        (*textLabel3)[i]->setDefaultTextColor(QColor("white"));
        (*textLabel3)[i]->setPos(-lineLength2/2 - 10 - (*textLabel3)[i]->boundingRect().width(),
                                 -temp-(*textLabel3)[i]->boundingRect().height()/2);
    }

    pathShow = new pathItem(lineLength2, lineLength3, frameToShow);
    pathShow->setParentItem(coordinateDoa2x);
    view3 = new QGraphicsView;
    view3->setStyleSheet("background-color: rgb(85, 170, 255)");
    view3->setScene(scene3);
    view3->setParent(this);
    view3->setGeometry(QRect(350, 20, 600, 280));
    view3->setFrameStyle(0);
    view3->show();

    //init tracking thread, link the signals and slots
    tracking1 = new trackingThread;
    connect(startButton, SIGNAL(clicked()),
            this, SLOT(startSlot()));
    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(stopSlot()));
    connect(tracking1, SIGNAL(signalDoa(short)),
            this, SLOT(updateDoa(short)));
    connect(tracking1, SIGNAL(signalParticlePos(particlePos*)),
            this, SLOT(updateParticleShow(particlePos*)));
    connect(tracking1, SIGNAL(signalTerminate()), this, SLOT(doaThreadTerminate()));

    file.close();
    fileStart.close();
    fileStop.close();
}

MainWindow::~MainWindow()
{
    delete cordIndicator;
    for(int i = 0; i < numOfLabel; i++)
    {
        delete (*textLabel)[i];
        (*textLabel)[i] = NULL;
        delete (*lineLabel)[i];
        (*lineLabel)[i] = NULL;
    }
    delete textLabel;
    textLabel = NULL;
    delete lineLabel;
    lineLabel = NULL;

    delete aboutButton;
    aboutButton = NULL;
    delete helpButton;
    helpButton = NULL;
    delete startButton;
    startButton = NULL;
    delete stopButton;
    stopButton = NULL;
    delete setButton;
    setButton = NULL;
    delete quitButton;
    quitButton = NULL;
    delete coordinateDoa;
    coordinateDoa = NULL;
    delete coordinateDoa2x;
    coordinateDoa2x = NULL;
    delete coordinateDoa2y;
    coordinateDoa2y = NULL;
    delete indicatorDoa;
    indicatorDoa = NULL;
    delete circularShap;
    circularShap = NULL;

    delete scene;
    scene = NULL;
    delete view;
    view = NULL;
    delete scene2;
    scene2 = NULL;
    delete view2;
    view2 = NULL;
    delete scene3;
    scene3 = NULL;
    delete view3;
    view3 = NULL;

    tracking1->terminate();
    usleep(4000000);  //wait to free the space
    delete tracking1;
    tracking1 = NULL;
}

void MainWindow::startSlot()
{
    //start tracking
    tracking1->setStart();
    tracking1->start();
}

void MainWindow::stopSlot()
{
    //stop tracking and set the indicator to be invisible
    tracking1->setStop();
    for(int i = 0; i < numParticle; i++)
    {
       (*particleIndicatorGroup)[i]->setVisible(false);
    }
    indicatorDoa->setVisible(false);
    particleDoaIndicator1->setVisible(false);
    cordIndicator->setVisible(false);
}

void MainWindow::doaThreadTerminate()
{
    //stop tracking thread,free space,set indicator invisible
    for(int i = 0; i < numParticle; i++)
    {
       (*particleIndicatorGroup)[i]->setVisible(false);
    }
    indicatorDoa->setVisible(false);
    particleDoaIndicator1->setVisible(false);
    cordIndicator->setVisible(false);
}

void MainWindow::updateDoa(short DoaToUpdate)
{
    //update the direct noisy DOA observations
    cordIndicator->setVisible(true);
    cordIndicator->setNewDoa(DoaToUpdate);
}

void MainWindow::updateParticleShow(particlePos *posGroup)
{
    //update the DOA results after particle filtering

    if(posGroup->state == true)
    {

        short meanDoa = posGroup->meanDoa;
        for(int i = 0; i < numParticle; i++)
        {
           (*particleIndicatorGroup)[i]->setVisible(true);
           (*particleIndicatorGroup)[i]->setNewDoa((*(posGroup->pos))[i]);
            indicatorDoa->setVisible(true);        
            indicatorDoa->setNewDoa(meanDoa);
        }
        particleDoaIndicator1->setVisible(true);
        particleDoaIndicator1->setNewDoa(meanDoa);
        pathShow->setNewDoa(meanDoa, true);
    }
    else
    {
        for(int i = 0; i < numParticle; i++)
        {
            (*particleIndicatorGroup)[i]->setVisible(false);
        }
        indicatorDoa->setVisible(false);
        particleDoaIndicator1->setVisible(false);
        pathShow->setNewDoa(0, false);
    }

}

