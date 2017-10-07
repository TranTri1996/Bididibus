#include <QGraphicsRectItem>
#include "rain.h"
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <qDebug>
rain::rain(int a,int b){
    setRect(0,0,5,6);
    Min=a; Max=b;
    setBrush(Qt::blue);
    Y=y();
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(4);
}
void rain::move(){
    setPos(x(),y()+2);
    if(y()>150) {
        Y = rand() % 150 + 1;
        int x= rand() % (Max-Min) + Min;
        setPos(x,Y);
    }
}
