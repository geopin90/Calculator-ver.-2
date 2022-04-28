#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(controller *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ctrl(c) {
    ui->setupUi(this);
    connect_buttons();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connect_buttons() {
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_zero, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_one, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_two, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_three, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_four, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_five, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_six, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_seven, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_eight, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_nine, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_o_par, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_c_par, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_deg, SIGNAL(clicked()), this, SLOT(button_clicked()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(function_clicked()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(function_clicked()));
}

void MainWindow::button_clicked() {
    QPushButton *number = (QPushButton*)sender();
    ui->lineEdit->insert(number->text());
}

void MainWindow::function_clicked() {
    QPushButton *number = (QPushButton*)sender();
    ui->lineEdit->insert(number->text() + "(");
}

void MainWindow::on_pushButton_mod_clicked() {
    ui->lineEdit->insert("%");
}

void MainWindow::on_pushButton_clear_clicked() {
    ui->lineEdit->clear();
    ui->lineEdit_x->clear();
}

void MainWindow::on_pushButton_backspace_clicked() {
    ui->lineEdit->backspace();
}

void MainWindow::on_pushButton_eq_clicked() {
    QString my_q = ui->lineEdit->text();
    QString my_x = ui->lineEdit_x->text();
    std::string s = my_q.toStdString();
    std::string x_s = my_x.toStdString();
    const char *str = s.c_str();
    const char *x = x_s.c_str();
    char *res = new char;
    ctrl->plain_calc(res, str, x);
    ui->lineEdit->setText(res);
    delete res;
}

void MainWindow::on_pushButton_plot_clicked() {
    QString my_q = ui->lineEdit->text();
    if (!my_q.isEmpty()) {
        std::string s = my_q.toStdString();
        const char *str = s.c_str();

        s21::Dialog_range mydialog(ctrl, str);
        mydialog.setModal(true);
        mydialog.exec();
    }
}
}  // namespace s21

