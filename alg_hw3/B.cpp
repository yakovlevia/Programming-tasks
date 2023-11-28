#include <bits/stdc++.h>

long double EPS = 1e-13;
std::vector<long double> cf(4);

long double my_pow(long double a, int n) {
    if (n == 2) {
        return a * a;
    }
    return std::pow(a, n);
}

long double generate(long double l, long double r, long double step) {
    std::vector <std::pair<long double, int>> lines;
    for (int i = 0; i < 2; i++) {
        long double pos = cf[i * 2];
        if (pos - 100 <= l && r <= pos + 100) {
            long double p1 = cf[i * 2 + 1] + std::sqrt(10000 - my_pow((l + r) / 2 - pos, 2));
            long double p2 = cf[i * 2 + 1] - std::sqrt(10000 - my_pow((l + r) / 2 - pos, 2));
            lines.push_back({p1 * step, 1});
            lines.push_back({p2 * step, -1});
        }
        if (pos - 70 <= l && r <= pos - 10) {
            long double p1 = cf[i * 2 + 1] + 30 + std::sqrt(900 - my_pow((l + r) / 2 - pos + 40, 2));
            long double p2 = cf[i * 2 + 1] + 30 - std::sqrt(900 - my_pow((l + r) / 2 - pos + 40, 2));
            lines.push_back({p1 * step, -1});
            lines.push_back({p2 * step, 1});
        }
        if (pos + 10 <= l && r <= pos + 70) {
            long double p1 = cf[i * 2 + 1] + 30 + std::sqrt(900 - my_pow((l + r) / 2 - pos - 40, 2));
            long double p2 = cf[i * 2 + 1] + 30 - std::sqrt(900 - my_pow((l + r) / 2 - pos - 40, 2));
            lines.push_back({p1 * step, -1});
            lines.push_back({p2 * step, 1});
        }
        if (pos - 60 <= l && r <= 60 + pos) {
            long double p1 = cf[i * 2 + 1] - 20;
            long double p2 = cf[i * 2 + 1] - 20 - std::sqrt(3600 - my_pow((l + r) / 2 - pos, 2));
            lines.push_back({p1 * step, -1});
            lines.push_back({p2 * step, 1});
        }
    }

    std::sort(lines.begin(), lines.end());

    int cnt = 0;
    long double prev = 0;
    long double res = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (cnt == 0) {
            prev = lines[i].first;
        }
        cnt += lines[i].second;
        if (cnt == 0) {
            res += lines[i].first - prev;
        }
    }

    return res;
}

int main() {
    for (auto &it: cf) {
        std::cin >> it;
    }
    long double ans = 0;
    long double step = 0.0001;
    for (long double i = -1101; i < 1101; i += step) {
        ans += generate(i, i + step, step);
    }
    std::cout << std::fixed << std::setprecision(5) << ans;
}
