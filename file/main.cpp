#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("BIDIDIBUS");
    w.resize(1200,680);
    w.show();
    return a.exec();
}
