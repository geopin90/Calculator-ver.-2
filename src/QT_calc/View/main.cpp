#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    s21::model m_m;
    s21::controller c_c(&m_m);
    QApplication a(argc, argv);
    s21::MainWindow w(&c_c);
    w.show();
    return a.exec();
}
