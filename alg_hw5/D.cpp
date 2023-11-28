#include <bits/stdc++.h>

const double INF = 1e14;
const double EPS = 1e-4;

void dfs(int v, std::vector <std::pair<double, double>> &g, double mx_size, std::vector<char> &used, int &cnt) {
    used[v] = 1;
    cnt++;
    //std::cout << v << "\n";
    for (int i = 0; i < g.size(); i++)  {
        //if (i == v) continue;
        if (!used[i] && std::sqrt(std::pow((g[v].first - g[i].first), 2) + std::pow((g[v].second - g[i].second), 2)) < mx_size) {
            dfs(i, g, mx_size, used, cnt);
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector <std::pair<double, double>> g(n);
    for (int i = 0; i < n; i++) {
        std::cin >> g[i].first >> g[i].second;
    }

    
    double l = 0;
    double r = INF;
    //std::cout << (std::abs(r - l) < EPS) << "\n";
    while (std::abs(r - l) > EPS) {
        double mid = (l + r) / 2;
        std::vector<char> used(n, 0);
        int cnt = 0;
        dfs(0, g, mid, used, cnt);
        //std::cout << (cnt == n) << " " << mid << "\n";
        if (cnt == n) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    std::cout << r;

}