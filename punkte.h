#include <QFile>
#include <QLabel>
#include <QTimer>
#include <QWidget>

class Punkte : public QWidget{
    Q_OBJECT
public:
    explicit Punkte(int breite);
    void start();
    void stop();
    QString serialize();
    void deserialize(QString spielStand);

private:
    int punkte = 0;
    int breite;
    QLabel *punkteLabel = new QLabel(QString::number(punkte));
    QTimer *timer;

private slots:
    void erhoehe();
};
