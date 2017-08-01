#-------------------------------------------------
#
# Project created by QtCreator 2016-07-15T21:56:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trackingPacked
TEMPLATE = app


SOURCES += main.cpp \
    audio_reader.cpp \
    doaResult.cpp \
    fft.cpp \
    myexception.cpp \
    Doa_Estimation.cpp
HEADERS  += \
    audio_reader.h \
    Doa_Estimation.h \
    fft.h \
    myexception.h \
    stdafx.h \
    doaResult.h

DISTFILES += \
    109_1_tracking_fast_s.wav \
    hamming.wav

RESOURCES +=
