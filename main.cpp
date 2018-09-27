#include <QApplication>
#include "meinwidget.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MeinWidget meinWidget;
    meinWidget.setGeometry(0,0,1100,600);
    meinWidget.show();
    return a.exec();
}
