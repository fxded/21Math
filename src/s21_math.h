#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_
#include <stdio.h>

#define s21_EPS 1e-12
#define s21_PI 3.14159265358979323846264338327950288
#define s21_EXP 2.7182818284590452353602874713526624

#define s21_INF 1.0 / 0.0
#define minus_s21_INF -1.0 / 0.0
#define s21_NAN 0.0 / 0.0

#define s21_is_INF(x) __builtin_isinf(x)

long double s21_sqrt(double x);
long double s21_max(long double a, long double b);
int s21_abs(int x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_exp(double x);
long double s21_fmod(double x, double y);
long double s21_fabs(double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_asin(double x);
int s21_fact(int i);
long double s21_acos(double x);
int s21_isnan(long double number);
int result_check(long double my_number, long double true_number);
long double new_s21_pow(double base, double exp);

long double s21_pow_int(double base, int exp);
long double s21_atan(double x);

#endif  // SRC_S21_MATH_H_
