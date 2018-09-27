#include <QWidget>
#include <QTimer>

class ZeichenFeld : public QWidget{
    Q_OBJECT
public:
    explicit ZeichenFeld(int breite, int hoehe);
    void start();
    void stop();
    void spielerLinks();
    void spielerRechts();
    QString serialize();
    void deserialize(QString spielStand);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int breite;
    int hoehe;
    QTimer *zeichenFeldTimer;
    QTimer *schwerkraftTimer;
    QTimer *hindernissTimer;
    QRect spieler;
    bool pause = true;
    std::vector<QRect> hindernisse;

private slots:
    void erzeugeHinderniss();
    void schwerkraft();
};
