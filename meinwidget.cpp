#include <QGridLayout>
#include <QtWidgets>
#include"meinwidget.h"

MeinWidget::MeinWidget(){
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);
    setAutoFillBackground(true);

    zeichenFeld = new ZeichenFeld(1000, 500);
    punkte = new Punkte(500);

    pauseButton = new QPushButton("Start");
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(spielPause()));

    QPushButton *speicherButton = new QPushButton("Speichern");
    connect(speicherButton, SIGNAL(clicked()), this, SLOT(speichern()));

    QPushButton *ladeButton = new QPushButton("Laden");
    connect(ladeButton, SIGNAL(clicked()), this, SLOT(laden()));

    QGridLayout *meinLayout = new QGridLayout;
    meinLayout->addWidget(punkte,0,0);
    meinLayout->addWidget(new QLabel(),0,1); //leer
    meinLayout->addWidget(speicherButton,0,2);
    meinLayout->addWidget(pauseButton,0,3);
    meinLayout->addWidget(ladeButton,0,4);
    meinLayout->addWidget(new QLabel(),0,5); //leer
    meinLayout->addWidget(new Leben(100, 30),0,6);
    meinLayout->addWidget(new QLabel(),0,7); //leer
    meinLayout->addWidget(zeichenFeld,1,0,1,7);
    meinLayout->addWidget(new QLabel(),2,0); //leer

    meinLayout->setColumnMinimumWidth(0,100);
    meinLayout->setColumnMinimumWidth(1,250);
    meinLayout->setColumnMinimumWidth(2,100);
    meinLayout->setColumnMinimumWidth(3,100);
    meinLayout->setColumnMinimumWidth(4,100);
    meinLayout->setColumnMinimumWidth(5,250);
    meinLayout->setColumnMinimumWidth(6,100);

    meinLayout->setColumnStretch(7,1);
    meinLayout->setRowStretch(2,1);
    meinLayout->setRowMinimumHeight(0,30);
    meinLayout->setRowMinimumHeight(1,500);
    meinLayout->setSpacing(0); //Button aneinander

    setLayout(meinLayout);
}
void MeinWidget::spielPause(){
   if(pause){
       start();
   } else{
       stop();
   }
}

void MeinWidget::start(){
    zeichenFeld->start();
    punkte->start();
    pauseButton->setText("Pause");
    pause = false;
}

void MeinWidget::stop(){
    zeichenFeld->stop();
    punkte->stop();
    pauseButton->setText("Fortsetzen");
    pause = true;
}

void MeinWidget::speichern(){
    pauseButton->setChecked(false); // pause
    repaint();
    QFileDialog dialog(this);
    QFile file;
    QString fileName = dialog.getSaveFileName(this,tr("Speichern Unter"), "", tr("Spielstand (*.spielstand)"));
    file.setFileName(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Fehler"), tr("Fehler") + fileName,QMessageBox::Ok); //Fehlermeldung
        return;
    }
    QTextStream out(&file); //holt alles aus Punkte und Zeichenfeld
    out << punkte->serialize(); //speichert punkte
    out << zeichenFeld->serialize(); // hier zeichenfeld
    file.close();
}

void MeinWidget::laden(){
    pauseButton->setChecked(false);
    repaint();
    QFileDialog dialog(this); //Ladefenster
    QFile file;
    QString fileName = dialog.getOpenFileName(this,tr("Laden"), "", tr("Spielstand (*.spielstand)"));
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Fehler"), tr("Fehler") + fileName,QMessageBox::Ok);
        return;
    }

    QString spielStand = file.readAll(); //Datei wird gelesen
    file.close();
    punkte->deserialize(spielStand); //ganzer Inhalt - punkte wird separat ausgelesen
    zeichenFeld->deserialize(spielStand);
}

void MeinWidget::keyPressEvent(QKeyEvent *event){ //Avatarsteurung
    if(event->key() == Qt::Key_Left){
        zeichenFeld->spielerLinks();
    } else if (event->key() == Qt::Key_Right) {
        zeichenFeld->spielerRechts();
    }
}
