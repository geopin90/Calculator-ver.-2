#include "model.h"

namespace s21 {
    void model::calcul(char *res, const char *str, const char *x_str) {
        std::stack<double> d_stack;
        struct Flags fl;
        init_flags(&fl);
        char **endptr = nullptr;
        double x = strtod(x_str, endptr), result;
        char buf[SIZE] = {};
        snprintf(buf, SIZE, "%s", str);
        parser(&fl, &d_stack, x, buf, &result);
        check_result(&fl, result, res);
    }

    void model::print_plot(const char *str, std::vector<double> *x,
    std::vector<double> *y, double x1, double x2) {
        std::stack<double> d_stack;
        struct Flags fl;
        char buf[SIZE] = {};
        double iks = x1;
        double step = fabs(x1 - x2) / 100000;
        while (iks <= x2) {
            init_flags(&fl);
            double ygrik;
            snprintf(buf, SIZE, "%s", str);
            parser(&fl, &d_stack, iks, buf, &ygrik);
            x->push_back(iks);
            y->push_back(ygrik);
            iks += step;
        }
    }

    void init_flags(struct Flags *f) {
        f->point = 0;
        f->flag_op = 0;
        f->flag_func = 0;
        f->flag_x = 0;
        f->flag_minus = 0;
        f->error = 0;
        f->ops = 0;
        f->nums = 0;
        f->funcs = 0;
        f->parenthesis = 0;
    }

    bool check_parenthesis(struct Flags *fl, const std::stack<const char*> *stc) {
        bool check = false;
        std::stack<const char*> temp = *stc;
        for (size_t i = 0; i < fl->point; i++) {
            if ((strcmp(temp.top(), "(")) == 0)
                check = true;
            temp.pop();
        }
        return check;
    }

    void check_flags(struct Flags *fl, const char *token) {
        const char *oper[] = {"^", "%", "*", "/", "+", "-"};
        const char *func[] = {"cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
        size_t i = 0;
        for (; i < 6; i++) {
            if ((strcmp(token, oper[i])) == 0)
                fl->flag_op = 1;
        }
        for (i = 0; i < 9; i++) {
            if ((strcmp(token, func[i])) == 0)
                fl->flag_func = 1;
        }
        if ((strcmp(token, "x")) == 0)
            fl->flag_x = 1;
    }

    void check_operands(struct Flags *fl, std::stack<const char*> *stc, char *token, char *out) {
        char buf[SIZE] = {};
        if (token[0] == '%') {
            if (fl->point > 0 && (stc->top()[0] == '^' || stc->top()[0] == '%')) {
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop(); fl->point--;
                strncat(out, buf, SIZE);
            }
            stc->push(token); fl->point++;
        } else if (token[0] == '^') {
            stc->push(token); fl->point++;
        } else if (token[0] == '*' || token[0] == '/') {
            if (fl->point > 0 && stc->top()[0] == '^') {
                while (fl->point > 0 && stc->top()[0] == '^') {
                    snprintf(buf, SIZE, "%s", stc->top());
                    stc->pop(); fl->point--;
                    strncat(out, buf, SIZE);
                }
            } else if (fl->point > 0 && (stc->top()[0] == '%')) {
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop(); fl->point--;
                strncat(out, buf, SIZE);
            } else if (fl->point > 0 && (stc->top()[0] == '*' || stc->top()[0] == '/')) {
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop(); fl->point--;
                strncat(out, buf, SIZE);
            }
            stc->push(token); fl->point++;
        } else if (token[0] == '+' || (token[0] == '-')) {
            if (fl->point > 0 && stc->top()[0] == '^') {
                while (fl->point > 0 && stc->top()[0] == '^') {
                    snprintf(buf, SIZE, "%s", stc->top());
                    stc->pop(); fl->point--;
                    strncat(out, buf, SIZE);
                }
            } else if (fl->point > 0 && (stc->top()[0] == '%')) {
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop(); fl->point--;
                strncat(out, buf, SIZE);
            } else if (fl->point > 0 && (stc->top()[0] == '*' || stc->top()[0] == '/')) {
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop(); fl->point--;
                strncat(out, buf, SIZE);
            } else if (fl->point > 0 && (stc->top()[0] == '+' || stc->top()[0] == '-')) {
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop(); fl->point--;
                strncat(out, buf, SIZE);
            }
            stc->push(token); fl->point++;
        }
    }

    bool check_dots(const char *token) {
        bool check = 1;
        size_t len = strlen(token), count = 0;
        for (size_t i = 0; i < len; i++) {
            if (token[i] == '.')
                count++;
        }
        if (count > 1) check = 0;
        return check;
    }

    void sort(struct Flags *fl, std::stack<const char*> *stc, char *in, char *out) {
        make_space_in(in);
        char buf[SIZE] = {};
        char space[] = " ", *token = NULL, *saveptr = NULL;
        for (token = strtok_r(in, space, &saveptr); token; token = strtok_r(NULL, space, &saveptr)) {
            if (!check_dots(token)) { fl->error = 1; }
            fl->flag_op = 0, fl->flag_func = 0;
            check_flags(fl, token);
            if ((token[0] >= '0' && token[0] <= '9') || (token[0] == '-' && token[1] != '\0')
            || token[0] == '.' || token[0] == 'x' || token[0] == 'e') {
                fl->nums++;
                if (out[0] != '\0') strncat(out, " ", SIZE);
                strncat(out, token, SIZE);
            } else if (fl->flag_op) {
                fl->ops++;
                check_operands(fl, stc, token, out);
            } else if (fl->flag_func) {
                fl->funcs++;
                stc->push(token);
                fl->point++;
            } else if (token[0] == '(') {
                stc->push(token);
                fl->point++;
                fl->parenthesis++;
            } else if (token[0] == ')') {
                if (check_parenthesis(fl, stc)) {
                    if (out[strlen(out)-1] != ' ') strncat(out, " ", SIZE);
                    while (stc->top()[0] != '(') {
                        snprintf(buf, SIZE, "%s", stc->top());
                        stc->pop();
                        fl->point--;
                        strncat(out, buf, SIZE);
                    }
                    snprintf(buf, SIZE, "%s", stc->top());
                    stc->pop();
                    fl->point--;
                    fl->parenthesis--;
                    if (fl->point) {
                        check_flags(fl, stc->top());
                        if (fl->flag_func) {
                            snprintf(buf, SIZE, "%s", stc->top());
                            stc->pop();
                            fl->point--;
                            strncat(out, buf, SIZE);
                        }
                    }
                } else {
                    fl->error = 1;
                }
            }
        }
        check_errors(fl);
        if (!fl->error) {
            while (fl->point > 0) {
                if (out[strlen(out)-1] != ' ') strncat(out, " ", SIZE);
                snprintf(buf, SIZE, "%s", stc->top());
                stc->pop();
                fl->point--;
                strncat(out, buf, SIZE);
            }
            out[strlen(out)] = '\0';
            make_space_out(out);
        }
    }

    void parser_func(struct Flags *fl, std::stack<double> *std, char *token) {
        double a = std->top(); std->pop();
        if (strcmp(token, "cos") == 0) {
            std->push(cos(a));
            fl->funcs++;
        } else if (strcmp(token, "sin") == 0) {
            std->push(sin(a));
            fl->funcs++;
        } else if (strcmp(token, "tan") == 0) {
            std->push(tan(a));
            fl->funcs++;
        } else if (strcmp(token, "acos") == 0) {
            std->push(acos(a));
            fl->funcs++;
        } else if (strcmp(token, "asin") == 0) {
            std->push(asin(a));
            fl->funcs++;
        } else if (strcmp(token, "atan") == 0) {
            std->push(atan(a));
            fl->funcs++;
        } else if (strcmp(token, "sqrt") == 0) {
            std->push(sqrt(a));
            fl->funcs++;
        } else if (strcmp(token, "ln") == 0) {
            std->push(log(a));
            fl->funcs++;
        } else if (strcmp(token, "log") == 0) {
            std->push(log10(a));
            fl->funcs++;
        }
    }

    void parser(struct Flags *fl, std::stack<double> *std, double x, char *in, double *result) {
        std::stack<const char*> temp;
        char out[SIZE] = {};
        sort(fl, &temp, in, out);
        if (!fl->error) {
            const char space[] = " ";
            char *token = NULL, *saveptr = NULL;
            char **endptr = nullptr;
            double a, b;
            for (token = strtok_r(out, space, &saveptr); token; token = strtok_r(NULL, space, &saveptr)) {
                if ((token[0] >= '0' && token[0] <= '9') || token[0] == '.'
                || (token[0] == '-' && token[1] != '\0')) {
                    std->push(strtod(token, endptr));
                    fl->nums++;
                } else if (token[0] == 'x') {
                    std->push(x);
                    fl->nums++;
                } else if (token[0] == '+') {
                    b = std->top(); std->pop();
                    a = std->top(); std->pop();
                    std->push(a + b);
                    fl->ops++;
                } else if (token[0] == '-') {
                    b = std->top(); std->pop();
                    a = std->top(); std->pop();
                    std->push(a - b);
                    fl->ops++;
                } else if (token[0] == '*') {
                    b = std->top(); std->pop();
                    a = std->top(); std->pop();
                    std->push(a * b);
                    fl->ops++;
                } else if (token[0] == '/') {
                    b = std->top(); std->pop();
                    a = std->top(); std->pop();
                    std->push(a / b);
                    fl->ops++;
                } else if (token[0] == '^') {
                    b = std->top(); std->pop();
                    a = std->top(); std->pop();
                    std->push(pow(a, b));
                    fl->ops++;
                } else if (token[0] == '%') {
                    b = std->top(); std->pop();
                    a = std->top(); std->pop();
                    std->push(fmod(a, b));
                    fl->ops++;
                } else {
                    parser_func(fl, std, token);
                }
            }
            *result = std->top(); std->pop();
        }
    }

    void check_result(struct Flags *fl, double result, char *str) {
        if (fl->error) {
            snprintf(str, SIZE, "%s", "ERROR");
        } else {
            snprintf(str, SIZE, "%.7lf", result);
            delete_zeros(str);
        }
        init_flags(fl);
    }

    void check_errors(struct Flags *fl) {
        if (fl->ops >= fl->nums) {
            fl->error = 1;
        } else if (fl->nums > 1 && !fl->funcs && !fl->ops) {
            fl->error = 1;
        } else if (!fl->nums && !fl->funcs && !fl->ops) {
            fl->error = 1;
        } else if (fl->parenthesis > 0) {
            fl->error = 1;
        }
    }

    void delete_zeros(char *str) {
        size_t count = 0, flag = 0;
        while (str[count++] != '\0')
            if (str[count] == '.')
                flag = 1;
        if (flag) {
            size_t len = strlen(str);
            size_t i = len - 1;
            while (str[i] == '0') {
                str[i] = '\0';
                i--;
            }
            len = strlen(str);
            if (str[len-1] == '.')
                str[len-1] = '\0';
        }
    }

    void make_space_in(char *in) {
        char buf[SIZE] = "";
        int flag = 0;
        size_t len = strlen(in), count = 0;
        for (size_t i = 0; i < len; i++) {
            if (in[i-1] == '(' && in[i] == '+') {
                continue;
            } else if ((in[i] == '*' || in[i] == '/' || in[i] == '+') && in[i-1] != ' ') {
                buf[count++] = ' ';
            } else if ((in[i-1] == '*' || in[i-1] == '/' || in[i-1] == '+') && in[i] != ' ') {
                buf[count++] = ' ';
            } else if (in[i-1] == 'e' && in[i] == '-') {
                flag++;
            } else if (in[i-1] == '(' && in[i] == '-') {
                buf[count++] = ' ';
                flag++;
            } else if (in[i] >= '0' && in[i] <= '9' && in[i-1] == '-' && flag) {
                flag--;
            } else if ((in[i] == '-' || in[i] == '^' || in[i] == '%') && in[i-1] != ' ' && in[i-1] != 'e') {
                buf[count++] = ' ';
            } else if ((in[i-1] == '-' || in[i-1] == '^' || in[i-1] == '%')
            && in[i] != ' ' && in[i-1] != 'e') {
                buf[count++] = ' ';
            } else if ((in[i] == '(' || in[i] == ')') && in[i-1] != ' ') {
                buf[count++] = ' ';
            } else if ((in[i-1] == '(' || in[i-1] == ')') && in[i] != ' ') {
                buf[count++] = ' ';
            }
            buf[count++] = in[i];
        }
        buf[count] = '\0';
        if (count > 0)
            snprintf(in, SIZE, "%s", buf);
    }

    void make_space_out(char *out) {
        char buf[SIZE] = "";
        size_t len = strlen(out), count = 0;
        for (size_t i = 0; i < len; i++) {
            if ((out[i] == '*' || out[i] == '/' || out[i] == '+') && out[i-1] != ' ') {
                buf[count++] = ' ';
            } else if (count > 0 && out[i] != ' '
            && (out[i-1] == '*' || out[i-1] == '/' || out[i-1] == '+')) {
                buf[count++] = ' ';
            } else if (count > 0 && out[i] == '-' && out[i-1] == 'e') {
                buf[count++] = out[i++];
            } else if (count > 0 && out[i] >= '0' && out[i] <= '9' && out[i-1] == '-') {
                buf[count++] = out[i++];
            } else if (count > 0 && (out[i] == '-' || out[i] == '^' || out[i] == '%') && out[i-1] != ' ') {
                buf[count++] = ' ';
            } else if (count > 0 && out[i] != ' '
            && (out[i-1] == '-' || out[i-1] == '^' || out[i-1] == '%')) {
                buf[count++] = ' ';
            } else if (count > 0 && (out[i] == '(' || out[i] == ')') && out[i-1] != ' ') {
                buf[count++] = ' ';
            } else if (count > 0 && out[i] != ' ' && (out[i-1] == '(' || out[i-1] == ')')) {
                buf[count++] = ' ';
            }
            buf[count++] = out[i];
        }
        buf[count] = '\0';
        if (count > 0)
            snprintf(out, SIZE, "%s", buf);
    }
}  // namespace s21
