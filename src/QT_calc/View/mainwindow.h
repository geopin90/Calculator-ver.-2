#ifndef SRC_QT_CALC_VIEW_MAINWINDOW_H_
#define SRC_QT_CALC_VIEW_MAINWINDOW_H_

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <string>
#include "../Controller/controller.h"
#include "plot.h"
#include "dialog_range.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(controller *c, QWidget *parent = nullptr);
    ~MainWindow();

 private slots:

    void connect_buttons();

    void button_clicked();

    void function_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_eq_clicked();

    void on_pushButton_plot_clicked();

    void on_pushButton_backspace_clicked();

    void on_pushButton_mod_clicked();

 private:
    Ui::MainWindow *ui;
    controller *ctrl;
};
}  // namespace s21
#endif  // SRC_QT_CALC_VIEW_MAINWINDOW_H_
