#ifndef QSCENE_H
#define QSCENE_H
#include <QGraphicsScene>
#include <QPen>
#include <QString>
#include <rain.h>
#include <QGraphicsTextItem>
#include <qmath.h>
#include <QWindow>
#include <QTest>
#include <QStack>
#include <QQueue>
#include <QTime>
#include <QCoreApplication>
#include <QLabel>
#include <QColor>
#include <QPalette>
#include <QMessageBox>
#include <QGraphicsPolygonItem>
#include <QFileDialog>
#include <QTextStream>
#include <QCompleter>
class qscene: public QGraphicsScene{
public:
    explicit qscene(QGraphicsScene *parent = 0);
    int c; // canh cua mot o vuong
    int l; // cai margin
    int Ox;
    int Oy;

    int B; // day cua mountain
    void Nets(QString s);
    void Descartes(QString s);
    void Heigh(QString s);
    int H;// chieu cao cua truc toa do
    int oxy; //bien chay cho truc toa do
    void Chart(QString s);
    void FillWater();
    void Delay(int time);
    void Arrow(int x,int y);
    void Oy_MT(int x,int y);
    void Ox_MT(int x,int y);


    QQueue <QPoint> qq;
    QQueue <QPoint> pp;
    QStack <QPoint> st;
    QVector <int> y_MT;
    QGraphicsPolygonItem *muiten;

private:
};
#endif // GSCENE_H
