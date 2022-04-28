#include "dialog_range.h"
#include "ui_dialog_range.h"

namespace s21 {
Dialog_range::Dialog_range(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog_range) {
    ui->setupUi(this);
}

Dialog_range::Dialog_range(controller *c, const char* text, QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog_range),
    d_ctrl(c), d_str(text) {
    ui->setupUi(this);
}

Dialog_range::~Dialog_range() {
    delete ui;
}


void Dialog_range::on_pushButton_ok_clicked() {
    double x1, x2, y1, y2;
    bool b1, b2, b3, b4;
    x1 = ui->lineEdit_xfrom->text().toDouble(&b1);
    x2 = ui->lineEdit_xto->text().toDouble(&b2);
    y1 = ui->lineEdit_yfrom->text().toDouble(&b3);
    y2 = ui->lineEdit_yto->text().toDouble(&b4);
    if (b1 && b2 && b3 && b4) {
        std::vector<double> x, y;
        d_ctrl->plot_calc(d_str, &x, &y, x1, x2);
        s21::Plot my_p(x1, x2, y1, y2, x, y, nullptr);
        my_p.setModal(true);
        my_p.exec();
    }
}


void Dialog_range::on_pushButton_cancel_clicked() {
    reject();
}

}  // namespace s21
