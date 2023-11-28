#include <bits/stdc++.h>

struct Point {
    long double x, y;

    Point operator - (Point a) const {
        return {x - a.x, y - a.y};
    }

    Point operator + (Point a) const {
        return {x + a.x, y + a.y};
    }

    Point operator * (double num) {
        return {x * num, y * num};
    }

    bool operator == (Point a) const {
        return fabs(x - a.x) < 1e-6 && fabs(y - a.y) < 1e-6;
    }

    double operator^(Point a) {
        return x * a.y - y * a.x;
    }

    double len() {
        return sqrt(x * x + y * y);
    }
};

bool cmp(Point a, Point b) {
    return (a ^ b) > 0 || (a ^ b) == 0 && a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
}

std::vector<Point> graham_convex_hull(std::vector<Point> points) {
    Point p0 = points[0];
    for (Point p : points)
        if (p.x < p0.x || (p.x == p0.x && p.y < p0.y))
            p0 = p;

    for (Point &x : points) {
        x.x -= p0.x;
        x.y -= p0.y;
    }
    sort(points.begin(), points.end(), cmp);

    std::vector<Point> hull;
    for (Point p : points) {
        if (hull.size() > 0 && hull.back() == p) continue;
        while (hull.size() >= 2 && ((p - hull.back()) ^ (hull[hull.size() - 2] - hull.back())) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    for (Point &x : hull) {
        x.x += p0.x;
        x.y += p0.y;
    }
    return hull;
}


double dist(Point a, Point b) {
    return (a - b).len();
}


std::mt19937 gen(131314);
std::uniform_real_distribution<double> dis(0.0, 1.0);

int main(){
    int precalc = 1;

    if (!precalc ) {
        std::freopen("output.txt", "w", stdout);

        for (int n = 3; n <= 10; n++) {
            long long ans = 0;

            for (int i = 0; i < 1e8; i++) {

                std::vector<Point> tmp;
                for (int j = 0; j < n; j++) {
                    // Point in triangle with vertices in A(0, 0), B(1, 0) and C(0, 1)
                    Point t = {dis(gen), dis(gen)};
                    if (t.x + t.y > 1) {
                        t.x = 1 - t.x;
                        t.y = 1 - t.y;
                    }
                    tmp.push_back(t);
                }

                std::vector<Point> hull = graham_convex_hull(tmp);

                if (hull.size() == n) {
                    ans += 1;
                }

            }
            std::cout << ans / 1e8 << ", ";
        }
    }
    else {
        std::vector<double> arr = {1, 0.666694, 0.305541, 0.101155, 0.0251854, 0.0048857, 0.00075527, 0.0000971500};

        std::vector<Point> vec(3);
        for (int i = 0; i < 3; i++) {
            std::cin >> vec[i].x >> vec[i].y;
        }

        int n;
        std::cin >> n;

        if (n <= 2) {
            std::cout << 1;
            return 0;
        }

        double d1 = dist(vec[0], vec[1]);
        double d2 = dist(vec[0], vec[2]);
        double d3 = dist(vec[1], vec[2]);

        if (fabs(d1 - d2 + d3) < 1e-5 || fabs(d1 + d2 - d3) < 1e-5 || fabs(-d1 + d2 + d3) < 1e-5) {
            std::cout << 0;
        }
        else {
            std::cout << std::fixed << std::setprecision(10);
            std::cout << arr[n - 3];
        }
    }
}