#ifndef SRC_QT_CALC_VIEW_PLOT_H_
#define SRC_QT_CALC_VIEW_PLOT_H_

#include <vector>
#include <QVector>
#include <QDialog>
#include "../qcustomplot.h"

namespace Ui {
class Plot;
}

namespace s21 {
class Plot : public QDialog {
    Q_OBJECT

 public:
    explicit Plot(QWidget *parent = nullptr);
    explicit Plot(double x1, double x2, double y1, double y2,
    std::vector<double> x, std::vector<double> y, QWidget *parent = nullptr);
    ~Plot();

 private:
    Ui::Plot *ui;
};
}  // namespace s21

#endif  // SRC_QT_CALC_VIEW_PLOT_H_
