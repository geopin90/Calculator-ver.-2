#ifndef SRC_QT_CALC_VIEW_DIALOG_RANGE_H_
#define SRC_QT_CALC_VIEW_DIALOG_RANGE_H_

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Dialog_range;
}

namespace s21 {
class Dialog_range : public QDialog {
    Q_OBJECT

 public:
    explicit Dialog_range(QWidget *parent = nullptr);
    explicit Dialog_range(controller *c, const char* text, QWidget *parent = nullptr);
    ~Dialog_range();

 private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

 private:
    Ui::Dialog_range *ui;
    controller *d_ctrl;
    const char* d_str;
};
}  // namespace s21

#endif  // SRC_QT_CALC_VIEW_DIALOG_RANGE_H_
