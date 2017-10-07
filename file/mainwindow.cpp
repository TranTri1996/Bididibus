#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <rain.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new qscene();
    t=0; q=0; speed=50;
    isrunning = true; Result = 0;
    kt_build = 0;
    ui->G_V->setFixedSize(950,550);
   // scene->setSceneRect(-100,-50,950,500);
    ui->G_V->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->G_V->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->G_V->setScene(scene);

    INTERFACE();

    des = new QTimer(this);
    run = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::wheelEvent(QWheelEvent *event)
{
    ui->G_V->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        double tile=1.15;
        if(event->delta()>0)
            ui->G_V->scale(tile,tile);
        else
            ui->G_V->scale(1/tile,1/tile);
}

void MainWindow::DESCARTES()
{
    scene->Descartes(S);
    if(scene->oxy == S.length()+3) {
        des->stop();
        disconnect(des,SIGNAL(timeout()),this,0);
        scene->Oy_MT(scene->Ox,scene->c*2);// add vao mui ten
        scene->Ox_MT(scene->Ox+scene->c*(S.length()+2),scene->Oy); //add vao mui ten
        scene->Chart(S);
    }
}

void MainWindow::RESET()
{
    run->stop();
    disconnect(run,SIGNAL(timeout()),this,0);

    des->stop();
    disconnect(des,SIGNAL(timeout()),this,0);

    scene = new qscene();
    ui->G_V->setScene(scene);

    Result=0;
    q=0;    t=0;
    scene->oxy=0;
    scene->y_MT.clear();
    ui->speed->setValue(1100);
    ui->speed->setEnabled(true);

    for(int i=0;i<8;i++)
    {
        ds_item[i]->setStyleSheet("background-color:white");
        ds_item[i]->setVisible(false);
    }
    ds_item[8]->setVisible(true); // cho logo hien ra

    ui->L_editInput->setText("");
    ui->L_editInput->setEnabled(true);
    ui->link_input->setText("");

    ui->btn_top->setVisible(true);
    ui->btn_top->setText("Stop");
    ui->btn_top->setEnabled(false);

    ui->btn_run->setEnabled(true);
    ui->btn_run->setText("Run");
    ui->btn_run->setEnabled(false);

    ui->pushButton_build->setEnabled(true);
    ui->btn_fromfile->setEnabled(true);

    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(false);

    ui->lcd_result->display(QString::number(0));
    ui->lcd_1->display(QString::number(0));
    ui->lcd_2->display(QString::number(0));
    ui->lcd_3->display(QString::number(0));

    scene->qq.clear();
    scene->pp.clear();
    scene->st.clear();
    Top.clear();

}
void MainWindow::INTERFACE()
{

    ui->lcd_1->display(QString::number(0));
    ui->lcd_2->display(QString::number(0));
    ui->lcd_3->display(QString::number(0));
    ui->lcd_result->display(QString::number(0));

    ui->btn_run->setEnabled(false);
    ui->btn_top->setEnabled(false);
    // thiet ke progressBar
    QPalette p = ui->progressBar->palette();
    p.setColor(QPalette::Highlight, QColor("#2D6DAE"));
    ui->progressBar->setVisible(false);
    ui->progressBar->setPalette(p);
    ui->progressBar->setStyleSheet("background-color:white");

    //set mau tung phan cho giao dien
    ui->L_editInput->setStyleSheet("background-color:white;border: 1px solid #2E41A0");

    ui->lcd_1->setStyleSheet("background-color:white;border: 1px solid #2E41A0");

    ui->lcd_2->setStyleSheet("background-color:white;border: 1px solid #2E41A0");
    ui->lcd_3->setStyleSheet("background-color:white;border: 1px solid #2E41A0");
    ui->link_input->setStyleSheet("background-color:white;border: 1px solid #2E41A0");
    ui->lcd_result->setStyleSheet("background-color:white ;border: 1px solid #2E41A0");
    ui->wg_process->setStyleSheet("background-color:white");
    ui->scroll_2->setStyleSheet("background-color:#538FCF");
    ui->scroll_horizontal->setStyleSheet("background-color:white");
    ui->scroll_1->setStyleSheet("background-color:#78A8DA");
    ui->wg_lon->setStyleSheet("background-color:#78A8DA");
    ui->G_V->setStyleSheet("background-color:white");
    ui->lcd_1->setPalette(Qt::black);
    ui->lcd_2->setPalette(Qt::black);
    ui->lcd_3->setPalette(Qt::black);
    ui->lcd_result->setPalette(Qt::black);
    // show ra ma gia cho nguoi dung
    MA_GIA();
    for(int i=0;i<8;i++)
        ds_item[i]->setVisible(false);

}

void MainWindow::on_pushButton_reset_clicked()
{
        RESET();
}

void MainWindow::CALCULATOR()
{
    scene->Arrow(scene->Ox+(int)scene->c/3+(q+1)*scene->c,scene->y_MT[q]);
    ds_item[2]->setStyleSheet("background-color:#C83625");

    ui->lcd_1->display(QString::number(q+1));
    if(S[q]=='\\')
    {
        Top.push(q);
        ds_item[0]->setText("  S[i] bang '\\'");
        ds_item[1]->setText("  luu chi so i vao ngan xep ST");
        ui->lcd_2->display(QString::number(Top.top()+1));
        ds_item[3]->setStyleSheet("background-color:#2E41A2");
        ds_item[4]->setStyleSheet("background-color:#407ABF");

        for(int j=5;j<=7;j++)
            ds_item[j]->setStyleSheet("background-color:white");
    }
    else if(S[q]=='/' && !Top.empty())
    {
        ds_item[0]->setText("  S[i] bang '/'");
        ds_item[1]->setText("  lay chi so i - dinh ngan xep ST");

        Result += q-Top.top();
        ui->lcd_3->display(QString::number(q-Top.top()));

        for(int j=3;j<=7;j++)
            ds_item[j]->setStyleSheet("background-color:white");

        ds_item[5]->setStyleSheet("background-color:#2E41A2");
        ds_item[6]->setStyleSheet("background-color:#407ABF");
        ds_item[7]->setStyleSheet("background-color:#407ABF");
        Top.pop();
        scene->FillWater();
    }
    else
    {
        ds_item[0]->setText("");
        ds_item[1]->setText("");
        for(int i=3;i<=7;i++)
        {
            ds_item[i]->setStyleSheet("background-color:white");
        }
    }
    ui->lcd_result->display(QString::number(Result));
    ui->progressBar->setValue(q+1);
    q++;

    if(q==S.length())
    {
        run->stop();
        disconnect(run,SIGNAL(timeout()),this,0);
        for(int k=0;k<S.length()*2/3;k++)
        {
            Rain[k]->timer->stop();
            scene->removeItem(Rain[k]);
        }
        ui->speed->setEnabled(false);
        ui->btn_top->setEnabled(false);
        ui->btn_run->setEnabled(true);
        ui->btn_run->setText("Run again");
        scene->Nets(S);
        scene->Nets(S);
        ds_item[0]->setVisible(false);
        ds_item[1]->setVisible(false);

        for(int j=0;j<=7;j++)
        {
            ds_item[j]->setVisible(false);
            ds_item[j]->setStyleSheet("background-color:white");
        }
        ds_item[8]->setVisible(true);
    }
}


void MainWindow::MA_GIA()
{
    QFont font;
    font.setPointSize(13);
    QVBoxLayout *layout = new QVBoxLayout();
    for(int i=0;i<9;i++)
    {
        ds_item[i] = new QLabel(ui->wg_process);
    }
    ds_item[0]->setText("");
    ds_item[1]->setText("");
    ds_item[2]->setText("for(i = 0;i < Len; i++)");
    ds_item[3]->setText("       if(S[i] == '\\')");
    ds_item[4]->setText("               ST.push(i);");
    ds_item[5]->setText("       else if(S[i]=='/' && ST.empty()!=0)");
    ds_item[6]->setText("               Sum += i - ST.top();");
    ds_item[7]->setText("               ST.pop();");
    QPixmap pixmap(":/new/prefix1/LOGODHCT.PNG");
    ds_item[8]->setPixmap(pixmap);
    ds_item[8]->setAlignment(Qt::AlignCenter);
    for(int i=0;i<8;i++)
    {
        ds_item[i]->setFont(font);
        layout->addWidget(ds_item[i]);
    }
    layout->addWidget(ds_item[8]);
    ui->wg_process->setLayout(layout);
}

void MainWindow::on_btn_run_clicked()
{

    if(ui->btn_run->text()!="Run")
    {
        QString temp=S;
        RESET();
        S = temp;
        ui->L_editInput->setText(S);
        scene->Heigh(S);
        scene->Nets(S);
        connect(des,SIGNAL(timeout()),this,SLOT(DESCARTES()));
        des->start(0);
        ui->btn_run->setEnabled(true);
        ui->L_editInput->setEnabled(false);
        ui->pushButton_build->setEnabled(false);
        scene->Ox = (scene->l)*scene->c;
        scene->Oy = (scene->l+scene->H)*scene->c;
        ui->btn_fromfile->setEnabled(false);
    }
    ds_item[8]->setVisible(false);
    connect(run,SIGNAL(timeout()),this,SLOT(CALCULATOR()));
    run->start(2100 - ui->speed->value());
    for(int i=0;i<S.length()*2/3;i++)
    {
        Rain[i] = new rain(num_rain*i,num_rain*(i+1));
        Rain[i]->setPos(x()+num_rain*i,y());
        scene->addItem(Rain[i]);
    }
    ui->progressBar->setMaximum(S.length());
    ui->progressBar->setVisible(true);
    ui->btn_top->setEnabled(true);

    for(int i=0;i<8;i++)
        ds_item[i]->setVisible(true);
    ui->btn_run->setEnabled(false);

}
void MainWindow::on_pushButton_build_clicked()
{
    int test=0;

    S = ui->L_editInput->text();
    num_rain = (S.length()+scene->l*2)*scene->c/(S.length()*2/3);
    //tu dong do tim test giong voi cac test vua nhap
    list.append(S);
    QCompleter *autocomplete = new QCompleter(list);
    ui->L_editInput->setCompleter(autocomplete);
    //kiem tra dau vao co hop li hay khong
    if(S.length()!=0)
    {
        for(int i=0;i< S.length() ;i++)
            if(S[i]!='/' && S[i]!='\\' && S[i]!='_')
            {
                test=1;
                QMessageBox::StandardButton click = QMessageBox::warning(this,"Warning","Nhập sai định dạng chuỗi vui lòng nhập lại!!");
                if(click==QMessageBox::Ok)
                    RESET();
                break;
            }
        if(!test)
        {
            scene->Heigh(S);
            scene->Nets(S);
            connect(des,SIGNAL(timeout()),this,SLOT(DESCARTES()));
            des->start(15);
            ui->btn_run->setEnabled(true);
            ui->L_editInput->setEnabled(false);
            ui->pushButton_build->setEnabled(false);
            ui->btn_fromfile->setEnabled(false);
            scene->Ox = (scene->l)*scene->c;
            scene->Oy = (scene->l+scene->H)*scene->c;
        }
    }
    else
        QMessageBox::warning(this,"Warning","Vui lòng nhập chuỗi vào Input!!");
}

void MainWindow::on_btn_top_clicked()
{
    if(ui->btn_top->text()=="Stop")
    {

        run->stop();
        for(int k=0;k<S.length()*2/3;k++)
        {
            Rain[k]->timer->stop();
            scene->removeItem(Rain[k]);
        }
        ui->btn_top->setText("Resume");
    }
    else
    {
        for(int k=0;k<S.length()*2/3;k++)
        {
            Rain[k] = new rain(num_rain*k,num_rain*(k+1));
            Rain[k]->setPos(x()+num_rain*k,y());
            scene->addItem(Rain[k]);
        }
        run->start(ui->speed->value());
        ui->btn_top->setText("Stop");
    }
}
void MainWindow::on_speed_valueChanged(int value)
{

    if(ui->btn_top->text()=="Stop")
        run->start(2100-value);
}

void MainWindow::on_btn_fromfile_clicked()
{
    QString s=ui->link_input->text();
    ui->link_input->setText(QFileDialog::getOpenFileName(this,"Open",s,"*.txt"));
    QFile file(ui->link_input->text());
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream input(&file);
        ui->L_editInput->setText(input.readLine());
        file.close();
    }
}


