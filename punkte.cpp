#include "punkte.h"
#include <QGridLayout>
#include <QtWidgets>

Punkte::Punkte(int breite){
    this->breite = breite;

    QGridLayout *punkteLayout = new QGridLayout;
    punkteLayout->addWidget(new QLabel("Punkte:"),0,0);
    punkteLayout->addWidget(punkteLabel,0,1);

    setLayout(punkteLayout);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(erhoehe()));
}

void Punkte::erhoehe(){
    punkte++;
    punkteLabel->setText(QString::number(punkte));
    update();
}

void Punkte::start(){ //jede Sekunde wird erhöht
    timer->start(1000);
}

void Punkte::stop(){
    timer->stop();
}

QString Punkte::serialize(){ //speichern der Punkte
    return QString("punkte\n") + QString::number(punkte) + QString("\nende\n");
}

void Punkte::deserialize(QString spielStand){ // Punkte werden eingelesen
   int i= 0;
   QStringList zeilen = spielStand.split(QRegExp("[\n]"),QString::SkipEmptyParts);  //teilt Inhalt in Zeilen
   //bis punkte
   while(zeilen[i] != "punkte"){
       i++;
   }
   i++;
   punkte = zeilen[i].toInt();
   punkteLabel->setText(QString::number(punkte));
   update();
}
