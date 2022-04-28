#include "controller.h"

namespace s21 {
    controller::controller(model *other) : m(other) {
    }

    void controller::plain_calc(char *res, const char *str, const char *x_str) {
        m->calcul(res, str, x_str);
    }

    void controller::plot_calc(const char *str,
    std::vector<double> *x, std::vector<double> *y, double x1, double x2) {
        m->print_plot(str, x, y, x1, x2);
    }

}  // namespace s21
