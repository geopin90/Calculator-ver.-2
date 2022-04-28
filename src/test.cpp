#include <gtest/gtest.h>
#include "../src/QT_calc/Model/model.h"

const size_t SIZE = 256;
const double EPS = 1e-7;

TEST(case0, test0) {
    char in[SIZE] = "x";
    s21::model m;
    std::vector<double> x, y;
    m.print_plot(in, &x, &y, -10, 10);
    ASSERT_EQ(x, y);
}

TEST(case1, test1) {
    char in[SIZE] = "1+2-3*4/5";
    double check = 0.6;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case1_1, test1_1) {
    char in[SIZE] = "20^3%3";
    double check = 2.0;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case2, test2) {
    char in[SIZE] = "(-2)*2";
    double check = -4.0;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case3, test3) {
    char in[SIZE] = "2-(-2)";
    double check = 4.0;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case4, test4) {
    char in[SIZE] = "(-2)/(-2)";
    double check = 1;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case5, test5) {
    char in[SIZE] = "sin(1)";
    double check = 0.8414709848;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case6, test6) {
    char in[SIZE] = "cos(1)";
    double check = 0.54030230586;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case7, test7) {
    char in[SIZE] = "tan(1)";
    double check = 1.55740772465;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case8, test8) {
    char in[SIZE] = "atan(0.5)";
    double check = 0.463647609;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case9, test9) {
    char in[SIZE] = "asin(0.5)";
    double check = 0.52359877559;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case10, test10) {
    char in[SIZE] = "acos(0.5)";
    double check = 1.0471975512;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case11, test11) {
    char in[SIZE] = "sqrt(0.5)";
    double check = 0.70710678118;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case12, test12) {
    char in[SIZE] = "ln(0.5)";
    double check = -0.69314718056;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case13, test13) {
    char in[] = "log(0.5)";
    double check = -0.30102999566;
    s21::model m_1;
    char out[SIZE] = {};
    m_1.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case14, test14) {
    char in[SIZE] = "2^2^3-4^1*2";
    double check = 248.0;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case15, test15) {
    char in[SIZE] = "sin(cos(1))";
    double check = 0.51439525852;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case16, test16) {
    char in[SIZE] = "sin(cos(sqrt(19 % 4)))";
    double check = -0.15986761197;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case17, test17) {
    char in[SIZE] = "2^2/(7%5+3)*sin(5-3)";
    double check = 0.72743794;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case18, test18) {
    char in[SIZE] = "1e4*1e-7";
    double check = 0.001;
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    char **endptr = nullptr;
    double res = strtod(out, endptr);
    ASSERT_NEAR(check, res, EPS);
}

TEST(case_err, test1) {
    char in[SIZE] = "sin(0.5";
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    ASSERT_STREQ(out, "ERROR");
}

TEST(case_err, test2) {
    char in[SIZE] = "1*2+";
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    ASSERT_STREQ(out, "ERROR");
}

TEST(case_err, test3) {
    char in[SIZE] = "1 2 3";
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    ASSERT_STREQ(out, "ERROR");
}

TEST(case_err, test4) {
    char in[SIZE] = "";
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    ASSERT_STREQ(out, "ERROR");
}

TEST(case_err, test5) {
    char in[SIZE] = "1.2.3 + 3.2.1";
    s21::model m;
    char out[SIZE] = {};
    m.calcul(out, in, "");
    ASSERT_STREQ(out, "ERROR");
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
