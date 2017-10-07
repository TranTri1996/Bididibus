#ifndef RAIN_H
#define RAIN_H
#include <QGraphicsRectItem>
#include <QObject>
class rain: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    rain(int a,int b);
    int Y;
    int Min,Max;
    QTimer * timer;
public slots:
    void move();
};

#endif // RAIN_H
