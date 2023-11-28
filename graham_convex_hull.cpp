#include <bits/stdc++.h>

// 1877

struct Point {
    double x, y;

    Point operator - (Point a) {
        return {x - a.x, y - a.y};
    }

    Point operator + (Point a) {
        return {x + a.x, y + a.y};
    }

    Point operator * (double num) {
        return {x * num, y * num};
    }


    bool operator == (Point a) {
        return x == a.x && y == a.y;
    }

  double operator^(Point a) {
        return x * a.y - y * a.x;
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

signed main(){
    int n;
    std::cin >> n;

    std::vector <Point> tmp1;
    for (int j = 0; j < n; j++) {
        double x, y;
        std::cin >> x >> y;
        tmp1.push_back({x, y});
    }

    std::vector <Point> tmp;
    tmp = tmp1;

    if (n >= 2) {

        tmp = graham_convex_hull(tmp1);

    }

    std::cout << tmp.size() << '\n';

    if (n % 2 == 0) {
        for (int i = 0; i < tmp.size(); i++) {
            std::cout << tmp[i].x << " " << tmp[i].y << '\n';
        }
    }
    else {
        for (int i = 0; i < tmp.size(); i++) {
            std::cout << tmp[tmp.size() - i - 1].x << " " << tmp[tmp.size() - i - 1].y << '\n';
        }
    }

    return 0;
}