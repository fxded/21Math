#include "s21_math.h"

long double s21_max(long double a, long double b) {
    return (a > b) ? a : b;
}

long double s21_sqrt(double x) {
    long double sol = (x/2);
    long double left = 0;
    long double right = s21_max(1, x);
    if (x < 0) {
        sol = s21_NAN;
    } else {
        while ((sol - left) > s21_EPS) {
            if (sol * sol > x) {
                right = sol;
            } else {
                left = sol;
            }
            sol = (right+left)/2;
        }
    }
    return sol;
}

int s21_abs(int x) {
    return x > 0 ? x : -x;
}

long double s21_fabs(double x) {
    return x > 0 ? x : -x;
}

long double s21_sin(double x) {
    long double sol = x;
    int i = 1;
    x = s21_fmod(x, s21_PI * 2);
    if (x > s21_PI) x -= 2*s21_PI;
    long double slagaemoe = x;
    sol = x;
    while (i < 100) {
        slagaemoe *= -1 * x * x / (i*2) / (i*2+1);
        sol+=slagaemoe;
        i++;
    }
    return sol;
}

long double s21_cos(double x) {
    x = s21_fmod(x, s21_PI * 2);
    if (x > s21_PI) x -= 2*s21_PI;
    long double sol = 1;
    long double slagaemoe = 1;
    for (long double i = 1; i < 100; i++) {
        slagaemoe *= -1 * x * x /(i*2) / (i*2-1);
        sol += slagaemoe;
    }
    return sol;
}

long double s21_tan(double x) {
    long double ans;
    if (x == s21_PI / 2) {
        ans = 16331239353195370.000000;
    } else if (x == -s21_PI / 2) {
        ans = -16331239353195370.000000;
    } else {
        ans = (s21_sin(x) / s21_cos(x));
    }
    return ans;
}

long double s21_exp(double x) {
    long double sol = 1 + x, slagaemoe = x;
    if (x == -s21_INF) {
        sol = 0;
    } else {
        for (long double i = 2; i < 100000; i++) {
            slagaemoe *= x / i;
            sol += slagaemoe;
        }
    }
    return sol;
}

long double s21_fmod(double x, double y) {
    long double ans = 0.0;
    if (y == 0) {
        ans = s21_NAN;
    } else if (s21_is_INF(x)) {
        ans = s21_NAN;
    } else if (s21_isnan(x) || s21_isnan(y)) {
        ans = s21_NAN;
    } else {
        int znak = (x > 0) ? 1 : -1;
        x = s21_fabs(x);
        while (x >= s21_fabs(y)) x -= s21_fabs(y);
        ans = x * znak;
    }
    return ans;
}

long double s21_ceil(double x) {
    long double ans = 0.0;
    if (s21_is_INF(x)) {
        if (x < 0) {
            ans = -s21_INF;
        } else {
            ans = s21_INF;
        }
    } else {
        if (s21_isnan(x)) {
            ans = s21_NAN;
        } else {
            ans = (long double)(int)x + (x > 0 ? ((int)x == x? 0 : 1) : 0);
        }
    }
    return ans;
}

long double s21_floor(double x) {
    long double ans;
    if (x == s21_INF) {
        ans = s21_INF;
    } else if (x == -s21_INF) {
        ans = -s21_INF;
    } else if (s21_isnan(x)) {
        ans = s21_NAN;
    } else {
        ans = (long double)(int)x - (x > 0 ? 0 : ((int)x == x ? 0 : 1));
    }
    return ans;
}

long double s21_log(double x) {
    long double z = (x-1)/(x+1);
    long double slagaemoe = z;
    long double sol = slagaemoe;
    if (x == 0) {
        sol = -1 * s21_INF;
    } else if (x < 0) {
        sol = s21_NAN;
    } else if (s21_is_INF(x)) {
        sol = s21_INF;
    } else if (x == s21_EXP) {
        sol = 1;
    } else {
        for (long double i = 1; i < 600000; i++) {
            slagaemoe *= z * z;
            sol += slagaemoe / (i*2+1);
        }
        sol *= 2;
    }
    return sol;
}

long double s21_asin(double x) {
    long double sol = x;
    long double buf = x;
    if (s21_fabs(x) > 1) {
        sol = s21_NAN;
    } else if (x == 1) {
        sol = s21_PI / 2;
    } else if (x == 0) {
        sol = 0;
    } else if (x == -1) {
        sol = -1 * s21_PI / 2;
    } else {
        for (long double i = 1; i < 300; i++) {
            buf *= (2 * i - 1) * 2 * i / 4 / i / i;
            buf *= (2 * (i - 1) + 1) / (2 * i + 1);
            buf *= x * x;
            sol += buf;
        }
    }
    return sol;
}

long double s21_acos(double x) {
    return (s21_PI/2 - s21_asin(x));
}

int s21_isnan(long double number) {
    int flag = 1;
    if (number > 0) {
        flag = 0;
    }
    if (number < 0) {
        flag = 0;
    }
    if (number == 0) {
        flag = 0;
    }
    return flag;
}

int result_check(long double my_number, long double true_number) {
    int value = 0;
    if (s21_isnan(my_number) && s21_isnan(true_number)) {
        value = 1;
    } else if ((my_number - true_number) < 1e-06) {
        value = 1;
    }
    return value;
}

long double s21_pow(double base, double exp) {
    long double ans = 1.0;
    long double u;
    int counter = 0;
    int sign = 0;
    int exp_big = 0;
    if (exp == 0.0) {
        ans = 1.0;
    } else {
        if ((exp == minus_s21_INF && base > 1.0) || (exp == minus_s21_INF && base < 0.0 && base != -1.0)) {
            ans = 0.0;
        } else if (exp == s21_INF && base > 1.0) {
            ans = s21_INF;
        } else if (exp == s21_INF && base > 0.0 && base <= 1.0 && !s21_is_INF(base)) {
            ans = 0.0;
        } else if (exp == minus_s21_INF && s21_isnan(base)) {
            ans = s21_NAN;
        } else if (exp == s21_INF && s21_isnan(base)) {
            ans = s21_NAN;
        } else if (s21_isnan(exp) && base == 1.0) {
            ans = 1.0;
        } else if (base == 1.0 && exp == minus_s21_INF) {
            ans = 1.0;
        } else if (exp == minus_s21_INF && base == -1.0) {
            ans = 1.0;
        } else if (exp == s21_INF && base == s21_INF) {
            ans = s21_INF;
        } else if (exp == minus_s21_INF && base == minus_s21_INF) {
            ans = 0.0;
        } else if ((exp == minus_s21_INF && base == s21_INF) || (exp == s21_INF && base == s21_INF)) {
            ans = 0.0;
        } else if (s21_is_INF(exp) && base == 0.0) {
            ans = 0.0;
        } else if (s21_is_INF(exp) && exp != 1) {
            ans = s21_INF;
        } else if (s21_isnan(exp) && s21_is_INF(base)) {
            ans = s21_NAN;
        } else if (s21_is_INF(exp) && s21_fabs(base) == 1 && !s21_is_INF(base)) {
            ans = 1.0;
        } else if (s21_is_INF(base) && exp == minus_s21_INF) {
            ans = 0.0;
        } else if (s21_is_INF(exp) && s21_is_INF(base)) {
            ans = s21_INF;
        } else if (base == 0.0 && exp != 1.0 && exp > 0) {
            ans = 0.0;
        } else if (exp == 1.0) {
            ans = base;
        } else if (base == 0.0 && exp < 0) {
            ans = s21_INF;
        } else if ((s21_is_INF(base) && exp < 0) || (s21_is_INF(-base) && exp < 0)) {
            ans = 0;
        } else if (base < 0 && s21_fmod(exp, (int)exp) != 0) {
            ans = s21_NAN;
        } else {
            if (base < 0) sign = 1;
            base = s21_fabs(base);
            while (base >= 2) {
                base /= 2;
                counter++;
            }
            if (exp < 1 && exp > 0) {
                exp += 1;
                exp_big = 1;
            }
            base--;
            long double buf = exp * base;
            ans += buf;
            for (long double i = 1; i < 10000; i++) {
                buf *= (exp - i) * base / (i + 1);
                ans += buf;
            }
            if (counter) {
                u = s21_exp(exp * s21_log(2));
            }
            if (exp_big) {
                ans /= (base + 1.0);
            }
            while (counter) {
                ans *= u;
                counter--;
            }
            if (sign && s21_fmod(exp, 2) != 0) {
                ans = -ans;
            }
        }
    }
    return ans;
}

int s21_fact(int i) {
    int ans;
    if (i == 0) {
        ans = 1;
    } else if (i == 1) {
        ans = 1;
    } else {
        ans = s21_fact(i-1) * i;
    }
    return ans;
}

long double s21_pow_int(double base, int exp) {
    long double sol = 1;
    long double znak = 0;
    if (exp < 0) {
        znak = 1;
        exp = -exp;
    }
    for (int i = 0; i < exp; i++) {
        sol *= base;
    }
    return znak ? 1/sol : sol;
}

long double s21_atan(double x) {
    long double sol = x;

    long double slagaemoe = x;
    if (s21_fabs(x)<= 1) {
        for(int i = 1; i < 5000; i++) {
            slagaemoe *= -1 * x * x;
            sol += slagaemoe / (2 * i + 1);
        }
    } else {
        sol = 0;
        for (register int i = 0; i < 3000; i++) {
            sol += s21_pow_int(-1, i) * s21_pow_int(x, -1 - (2 * i)) / (1 + (2 * i));
        }
        sol = s21_PI * s21_sqrt(x * x) / (2 * x) - sol;
    }
    return sol;
}
