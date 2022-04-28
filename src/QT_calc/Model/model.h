#pragma once

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <stack>

namespace s21 {
const size_t SIZE = 256;
struct Flags {
    size_t point;
    size_t flag_op;
    size_t flag_func;
    size_t flag_x;
    size_t flag_minus;
    //  error flags
    size_t error;
    size_t ops;
    size_t nums;
    size_t funcs;
    size_t parenthesis;
};

class model {
 public:
    model() {}
    ~model() {}
    void calcul(char *res, const char *str, const char *x_str);
    void print_plot(const char *str, std::vector<double> *x, std::vector<double> *y, double x1, double x2);
};
    void init_flags(struct Flags *f);
    bool check_parenthesis(struct Flags *fl, const std::stack<const char*> *stc);
    void check_flags(struct Flags *fl, const char *token);
    void check_operands(struct Flags *fl, std::stack<const char*> *stc, char *token, char *out);
    bool check_dots(const char *token);
    void sort(struct Flags *fl, std::stack<const char*> *stc, char *in, char *out);
    void parser_func(struct Flags *fl, std::stack<double> *std, char *token);
    void parser(struct Flags *fl, std::stack<double> *std, double x, char* in, double *result);
    void check_result(struct Flags *fl, double result, char *str);
    void check_errors(struct Flags *fl);
    void delete_zeros(char *str);
    void make_space_in(char *in);
    void make_space_out(char *out);
}  // namespace s21
