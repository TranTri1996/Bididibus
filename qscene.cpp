#include "qscene.h"


qscene::qscene(QGraphicsScene *parent)
    :QGraphicsScene(parent)
{
    c =30;
    l = 4;
    oxy=0;
}
void qscene::Delay(int time)
{
    QTime dieTime= QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void qscene::Nets(QString s)
{
    QPen pen(Qt::black,1);
    int Len = s.length();
    for(int i= 1;i<=(Len+2*l);i++)
        addLine(i*c,0,i*c,(H+l+3)*c,pen);
    for(int i= 1;i<(H+2*l-1);i++)
        addLine(0,i*c,(Len+2*l+1)*c,i*c,pen);
}

void qscene::Descartes(QString s)
{
    QPen pen(Qt::red,3);
    QFont font;
    font.setPointSize(12);
    QGraphicsTextItem *item;

    if(oxy<=s.length()+1)
    {
        item = addText(QString::number(oxy));
        item->setFont(font);
        item->setPos((l+oxy)*c,(l+H+1)*c);
    }
    addLine(c*l,c*(l+H),(l+oxy)*c,c*(l+H),pen);
    if(oxy<=H+2)
    {
        addLine(c*l,c*(l+H),c*l,(l+H-oxy)*c,pen);
        if(oxy<=H+1&&oxy)
        {
            item= addText(QString::number(oxy));
            item->setFont(font);
            item->setPos(c*(l-1),(l+H-oxy)*c);
        }
    }
    oxy++;
}

void qscene::Heigh(QString s)
{
    int temp=1;
    int T=temp;
    B=temp;
    for(int i=0;i<s.length();i++)
    {
        if(s[i] == '\\')
            temp--;
        else if(s[i]=='/')
            temp++;
        T=qMax(T,temp);
        B=qMin(B,temp);
    }
    H = T-B;
}
void qscene::Chart(QString s)
{
    int y;
    int x=Ox+c;
    QPen pen(Qt::blue,2);

    if(B==1) y=Oy-(qAbs(B))*c;
    else y=Oy-(qAbs(B)+2)*c;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='/')
        {
            if(!st.empty())
            {
                qq.push_back(QPoint(x+c,y-c));
                qq.push_back(QPoint(x,y));

                pp.push_back(st.top());
                st.pop();
                pp.push_back(st.top());
                st.pop();
            }
            addLine(x,y,x+c,y-c,pen);

            x+=c;
            y-=c;
            y_MT.push_back(y-3*c);
        }
        else if(s[i]=='\\')
        {
            st.push(QPoint(x,y));
            st.push(QPoint(x+c,y+c));
            addLine(x,y,x+c,y+c,pen);
            y_MT.push_back(y-3*c);
            x+=c;
            y+=c;
        }
        else
        {
            addLine(x,y,x+c,y,pen);
            y_MT.push_back(y-3*c);
            x+=c;
        }
        if(s.length()<45) Delay(80);
        else Delay(5);
    }
}
void qscene::FillWater()
{
    QPen pen(Qt::blue);
    QBrush brush(Qt::blue);

    QPolygon polygon;

        polygon <<qq.front();
        qq.pop_front();
        polygon <<qq.front();
        qq.pop_front();

        polygon <<pp.front();
        pp.pop_front();
        polygon <<pp.front();
        pp.pop_front();

    addPolygon(polygon,pen,brush);
}
void qscene::Arrow(int x, int y)
{
    QPen pen(Qt::blue);
    QBrush brush(Qt::blue);
    QPolygon polygon;
    polygon<<QPoint(x,y);
    polygon<<QPoint(x,y+2*c);
    polygon<<QPoint(x-8,y+2*c);
    polygon<<QPoint(x+5,y+2*c+18);
    polygon<<QPoint(x+18,y+2*c);
    polygon<<QPoint(x+10,y+2*c);
    polygon<<QPoint(x+10,y);
    muiten = addPolygon(polygon);
    muiten->setBrush(brush);
    Delay(300);
    removeItem(muiten);
}

void qscene::Oy_MT(int x, int y)// mui ten cua truc Oy
{
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    QPolygon polygon;
    polygon<<QPoint(x+5,y);
    polygon<<QPoint(x,y-10);
    polygon<<QPoint(x-5,y);
    addPolygon(polygon,pen,brush);
}
void qscene::Ox_MT(int x, int y)// mui ten cua truc Ox
{
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    QPolygon polygon;
    polygon<<QPoint(x,y+5);
    polygon<<QPoint(x+10,y);
    polygon<<QPoint(x,y-5);
    addPolygon(polygon,pen,brush);

}

