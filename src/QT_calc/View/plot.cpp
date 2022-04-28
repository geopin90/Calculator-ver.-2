#include "plot.h"
#include "ui_plot.h"

namespace s21 {

Plot::Plot(QWidget *parent) :
    QDialog(parent), ui(new Ui::Plot) {
    ui->setupUi(this);
    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-10, 10);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

Plot::Plot(double x1, double x2, double y1, double y2,
           std::vector<double> x, std::vector<double> y, QWidget *parent) :
    QDialog(parent), ui(new Ui::Plot) {
    ui->setupUi(this);
    ui->widget->xAxis->setRange(x1, x2);
    ui->widget->yAxis->setRange(y1, y2);

    QVector<double> qx = QVector<double>(x.begin(), x.end());
    QVector<double> qy = QVector<double>(y.begin(), y.end());

    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
    ui->widget->graph(0)->addData(qx, qy);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
}

Plot::~Plot() {
    delete ui;
}
}  // namespace s21
