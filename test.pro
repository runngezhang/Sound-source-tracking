#-------------------------------------------------
#
# Project created by QtCreator 2016-07-13T23:03:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += \
    dsResult/trackingthread.cpp \
    GUI/indicator.cpp \
    GUI/main.cpp \
    GUI/mainwindow.cpp \
    GUI/coordinateIndicator.cpp \
    GUI/circularIndicator.cpp \
    particles2D/particle2d.cpp \
    GUI/particleIndicator.cpp \
    particles2D/particlePos.cpp \
    GUI/pathitem.cpp

HEADERS  += \
    dsResult/audio_reader.h \
    dsResult/fft.h \
    dsResult/myexception.h \
    dsResult/stdafx.h \
    dsResult/trackingthread.h \
    GUI/indicator.h \
    GUI/mainwindow.h \
    GUI/coordinateIndicator.h \
    GUI/circularIndicator.h \
    GUI/particleIndicator.h \
    particles2D/particle2d.h \
    particles2D/particlePos.h \
    GUI/pathitem.h \
    dsResult/doa_estimation.h

FORMS    += \
    mainwindow.ui

SUBDIRS += \
    dsResult/trackingPacked.pro \
    dsResult/trackingPacked.pro

RESOURCES += \
    resources.qrc
DISTFILES += \
    dsResult/109_1_tracking_fast_s.wav \
    dsResult/hamming.wav

INCLUDEPATH += \
    dsResult \
    GUI \
    particles2D

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/release/ -lDoa_Estimation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/ -lDoa_Estimation
else:unix: LIBS += -L$$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ -lDoa_Estimation

INCLUDEPATH += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/release/libDoa_Estimation.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/libDoa_Estimation.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/release/Doa_Estimation.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug/Doa_Estimation.lib
else:unix: PRE_TARGETDEPS += $$PWD/build-Doa_Estimation-Desktop_Qt_5_7_0_MinGW_32bit-Debug/libDoa_Estimation.a
