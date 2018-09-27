#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include "zeichenfeld.h"
#include "leben.h"
#include "punkte.h"

class MeinWidget : public QWidget{
    Q_OBJECT
public:
    explicit MeinWidget();

private:
    ZeichenFeld *zeichenFeld;
    Punkte *punkte;
    QPushButton *pauseButton;
    bool pause = true;

protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void spielPause();
    void start();
    void stop();
    void speichern();
    void laden();
};
