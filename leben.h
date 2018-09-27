#include <QWidget>

class Leben : public QWidget{
    Q_OBJECT
public:
    explicit Leben(int breite, int hoehe);


protected:
    void paintEvent(QPaintEvent *event);

private:
    int breite;
    int hoehe;

    QRect erzeugeLeben(int index);
};
