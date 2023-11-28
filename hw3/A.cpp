#include <bits/stdc++.h>

long double EPS = 1e-13;
std::vector<long double> cf(5);

long double f(long double x) {
    long double k = 0;
    for (int j = 0; j < 5; j++) {
        k += cf[j] * std::pow(x, (long double) j);
    }
    return 1 / k;
}

long double get_simple_int(long double l, long double r) {
    return (r - l) / 6 * (f(l) + 4 * f((l + r) / 2) + f((r)));
}

long double get_int_adapt(long double l, long double r, int h = 0) {
    if (h < 25) {
        long double int_l = get_simple_int(l, (l + r) / 2);
        long double int_r = get_simple_int((l + r) / 2, r);
        long double int_lr = get_simple_int(l, r);
        if (std::abs(int_l + int_r - int_lr) < 15 * EPS) {
            return int_lr;
        }
        else {
            return get_int_adapt(l, (l + r) / 2) + get_int_adapt((l + r) / 2, r);
        }
    }
    return get_simple_int(l, r);
}

int main() {
    for (auto &it: cf) {
        std::cin >> it;
    }
    std::cout << std::fixed << std::setprecision(10);
    long double ans = get_int_adapt(-1e6, 1e6);
    std::cout << ans;
}