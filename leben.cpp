#include<QPainter>
#include "leben.h"

Leben::Leben(int breite, int hoehe){
    this->breite = breite;
    this->hoehe = hoehe;
}

void Leben::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);
    painter.setBrush(Qt::red);

    for(int i = 0; i < 3;i++){
       painter.drawEllipse(erzeugeLeben(i));
    }
    painter.end();
}

QRect Leben::erzeugeLeben(int index){
    QRect lebenKreis;

    // 11 weil sonst die das 1. leben am rand ist
    int x = breite - 11 - index * 15;
    int y = hoehe / 2;

    lebenKreis.setX(x);
    lebenKreis.setY(y);
    lebenKreis.setWidth(10);
    lebenKreis.setHeight(10);

    return lebenKreis;
}