#pragma once
#include "../Model/model.h"
#include <vector>

namespace s21 {
class controller {
 private:
    model *m;
 public:
    explicit controller(model *other);
    void plain_calc(char *res, const char *str, const char *x_str);
    void plot_calc(const char *str, std::vector<double> *x, std::vector<double> *y, double x1, double x2);
};
}  //  namespace s21
