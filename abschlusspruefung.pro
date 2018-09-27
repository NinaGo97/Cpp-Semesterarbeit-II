QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modulabschlusspruefung_gollwig
TEMPLATE = app


HEADERS = \
   zeichenfeld.h \
   leben.h \
   meinwidget.h \
   punkte.h

SOURCES = \
   zeichenfeld.cpp \
   leben.cpp \
   main.cpp \
   meinwidget.cpp \
   punkte.cpp

CONFIG += c++11
