#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <qscene.h>
#include <QVBoxLayout>
#include <QFont>
#include <QTimer>
#include <QWheelEvent>
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void wheelEvent(QWheelEvent *event);
    ~MainWindow();
private slots:
    void DESCARTES();
    void on_pushButton_build_clicked();
    void on_pushButton_reset_clicked();
    void on_speed_valueChanged(int value);
    void on_btn_top_clicked();
    void on_btn_fromfile_clicked();
    void on_btn_run_clicked();
    void CALCULATOR();



private:
    void RESET();
    void INTERFACE();
    void MA_GIA();
    Ui::MainWindow *ui;
    QTimer *des;
    QString S;
    qscene *scene;
    rain *Rain[1000];
    int num_rain; //so luong hat mua;
    QLabel *ds_item[9];
    QList<QString> list;
    QStack<int> Top;
    bool isrunning;
    int t;
    int q;// bien chay cho timer run
    int speed;

    int kt_build;//kiem tra nut build co nhan hay chua
    int Result;
    QTimer *run;

};

#endif // MAINWINDOW_H
