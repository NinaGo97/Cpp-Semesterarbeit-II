#include <QLabel>
#include <QKeyEvent>
#include <QPainter>
#include <QTimerEvent>
#include "zeichenfeld.h"

ZeichenFeld::ZeichenFeld(int breite, int hoehe){
    this->breite = breite;
    this->hoehe = hoehe;
    spieler.setRect((breite - 20) / 2, hoehe - 20 - 2, 20, 20); //spieler

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::yellow);
    setPalette(pal);
    setAutoFillBackground(true);

    zeichenFeldTimer = new QTimer();
    connect(zeichenFeldTimer, SIGNAL(timeout()),this, SLOT(update()));

    hindernissTimer = new QTimer();
    connect(hindernissTimer, SIGNAL(timeout()),this, SLOT(erzeugeHinderniss()));

    schwerkraftTimer = new QTimer();
    connect(schwerkraftTimer, SIGNAL(timeout()),this, SLOT(schwerkraft()));

    srand((int)time(nullptr)); //Zufallszahlen werden mit der Zeit berechnet

}
void::ZeichenFeld::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);

    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(spieler);


    painter.setPen(Qt::black);
    painter.setBrush(Qt::green);

    for(QRect h : hindernisse){ //geht Objekte aus der Liste durch for each schleife
        painter.drawRect(h);
    }

    painter.end();
}

void ZeichenFeld::start(){
  zeichenFeldTimer->start(10);
  hindernissTimer->start(1000);
  schwerkraftTimer->start(10);
  pause = false;
}

void ZeichenFeld::stop(){
  zeichenFeldTimer->stop();
  hindernissTimer->stop();
  schwerkraftTimer->stop();
  pause = true;
}

QString ZeichenFeld::serialize(){ // speichern der Hindernisse
    QString str = QString("spieler\n") + QString::number(spieler.x()) + QString("\nende\n");
    str += QString("hindernisse\n");
    for(QRect h : hindernisse){
        str += (QString::number(h.x()));
        str += "\n";
        str += (QString::number(h.y()));
        str += "\n";
    }
    str += "end\n";
    return str;
}

void ZeichenFeld::deserialize(QString spielStand){
    int i = 0;
    QStringList zeilen = spielStand.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    while(zeilen[i] != "spieler" ){
        i++;
    }
    i++;
    int x = zeilen[i].toInt();
    spieler.moveLeft(x);

    while(zeilen[i] != "hindernisse"){
        i++;
    }

    hindernisse.clear();
    i++;
    while(zeilen[i] != "end"){
        int x = zeilen[i].toInt();
        i++;
        int y = zeilen[i].toInt();
        QRect hinderniss;
        hinderniss.setRect(x,y,10, 10);
        hindernisse.push_back(hinderniss);
        i++;
    }
    update();
}

void ZeichenFeld::spielerRechts(){ //Position des Spielers
    if(pause == false){
        if(spieler.right() + 20 < breite - 2){
            spieler.moveRight(spieler.right() + 20);
        }else {
            spieler.moveRight(breite - 2);
        }
    }
}

void ZeichenFeld::spielerLinks(){
    if(pause == false){
        if(spieler.left() - 20 > 1){
            spieler.moveLeft(spieler.left() - 20);
        }else {
            spieler.moveLeft(1);
        }
    }
}

void ZeichenFeld::erzeugeHinderniss(){ //random Hindernisse werden erzeugt
    int x = (rand() % (breite - 11)) + 1;
    QRect hinderniss;
    hinderniss.setRect(x,1,10,10);
    hindernisse.push_back(hinderniss);
}

void ZeichenFeld::schwerkraft(){ //Geschwindigkeit der Hindernisse
    for(std::vector<QRect>::iterator it = hindernisse.begin(); it != hindernisse.end(); ++it){
        if(it->top() == hoehe){
            hindernisse.erase(it);
        } else {
            it->moveTop(it->top() + 1);
        }
    }
}
