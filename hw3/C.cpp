#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

double EPS = 1e-9;


auto start = std::chrono::high_resolution_clock::now();
auto end = std::chrono::high_resolution_clock::now();

struct Sector {
  double x;
  double y;
  double r;
  double s;
  double a;

  double x1, x2, y1, y2;

    Sector(){}

    Sector(double _x, double _y, double _r,double _s, double _a) : x(_x), y(_y), r(_r), s(_s), a(_a) {
        x1 = _x + _r * std::cos(_a + _s);
        x2 = _x + _r * std::cos(_s);
        y1 = _y + _r * std::sin(_a + _s);
        y2 = _y + _r * std::sin(_s);
    }
};

void check_rad(Sector &cur, double mid, std::vector <std::pair<double, int>> &lines) {
    if (mid < cur.x - cur.r || mid > cur.x + cur.r) return;
    
    double val_up = cur.y + sqrt(cur.r * cur.r - (mid - cur.x) * (mid - cur.x));
    double val_down = cur.y - sqrt(cur.r * cur.r - (mid - cur.x) * (mid - cur.x));

    if (cur.s + cur.a >= 0 && cur.s + cur.a <= M_PI && cur.x1 <= mid && mid <= cur.x2) {
        lines.push_back({val_up, 1});
    }
    else if (cur.s + cur.a >= M_PI && cur.s + cur.a <= 2 * M_PI) {
        if (cur.s <= M_PI) {
            if (cur.x - cur.r <= mid && mid <= cur.x2) {
                lines.push_back({val_up, 1});
            }
            if (cur.x - cur.r <= mid && mid <= cur.x1) {
                lines.push_back({val_down, -1});
            }
        }
        else {
            if (cur.x2 <= mid && mid <= cur.x1) {
                lines.push_back({val_down, -1});
            }
        }
    }
    else if (cur.s + cur.a >= 2 * M_PI && cur.s + cur.a <= 3 * M_PI) {
        if (cur.s <= M_PI) {
            if (cur.x - cur.r <= mid && mid <= cur.x2) {
                lines.push_back({val_up, 1});
            }
            if (cur.x1 <= mid && mid <= cur.x + cur.r) {
                lines.push_back({val_up, 1});
            }
            lines.push_back({val_down, -1});
        }
        else if (M_PI <= cur.s && cur.s <= 2 * M_PI) {
            if (cur.x1 <= mid && mid <= cur.x + cur.r) {
                lines.push_back({val_up, 1});
            }
            if (cur.x2 <= mid && mid <= cur.x + cur.r) {
                lines.push_back({val_down, -1});
            }
        }
    }
    else if (cur.s + cur.a >= 3 * M_PI && cur.s + cur.a <= 4 * M_PI) {
        lines.push_back({val_up, 1});
        if (cur.x - cur.r <= mid && mid <= cur.x1) {
            lines.push_back({val_down, -1});
        }
        if (cur.x2 <= mid && mid <= cur.x + cur.r) {
            lines.push_back({val_down, -1});
        }
    }
}

void line1(Sector &cur, double mid, std::vector <std::pair<double, int>> &lines) {
    if (cur.x1 >= cur.x) {
        if (cur.x <= mid && mid <= cur.x1) {
            lines.push_back({(cur.y + (cur.y1 - cur.y) * ((mid - cur.x) / (cur.x1 - cur.x))), 1});
        }
    }
    else {
        if (cur.x1 <= mid && mid <= cur.x) {
            lines.push_back({(cur.y + (cur.y1 - cur.y) * ((mid - cur.x) / (cur.x1 - cur.x))), -1});
        }
    }
}

void line2(Sector &cur, double mid, std::vector <std::pair<double, int>> &lines) {
    if (cur.x2 <= cur.x) {
        if (cur.x2 <= mid && mid <= cur.x) {
            lines.push_back({(cur.y + (cur.y2 - cur.y) * ((mid - cur.x) / (cur.x2 - cur.x))), 1});
        }
    }
    else {
        if (cur.x <= mid && mid <= cur.x2) {
            lines.push_back({(cur.y + (cur.y2 - cur.y) * ((mid - cur.x) / (cur.x2 - cur.x))), -1});
        }
    }
}

void make_lines(std::vector <std::pair<double, int>> &lines, std::vector<Sector> &vec, double mid) {
    for (int i = 0; i < vec.size(); i++) {
        check_rad(vec[i], mid, lines);
        line1(vec[i], mid, lines);
        line2(vec[i], mid, lines);
    }
}

double get_line_s(double mid, std::vector<Sector> &vec) {
    std::vector <std::pair<double, int>> lines;
    make_lines(lines,vec, mid);

    std::sort(lines.begin(), lines.end());

    int cnt = 0;
    double prev = 0;
    double res = 0;
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

double get_simple_int(double l, double r, std::vector<Sector> &vec) {
    return (r - l) / 6 * (get_line_s(l, vec) + 4 * get_line_s((l + r) / 2, vec) + get_line_s(r, vec));
}

double get_adapt_simp(double l, double r, std::vector<Sector> &vec, int h = 0) {
    double int_l = get_simple_int(l, (l + r) / 2, vec);
    double int_r = get_simple_int((l + r) / 2, r, vec);
    double int_lr = get_simple_int(l, r, vec);
    if (std::abs(int_l + int_r - int_lr) < EPS) {
        return int_l + int_r;
    }
    else {
        return get_adapt_simp(l, (l + r) / 2, vec) + get_adapt_simp((l + r) / 2, r, vec);
    }
}


std::istream& operator >> (std::istream& in, Sector& sec) {
    double x, y, r, s, a;
    in >> x >> y >> r >> s >> a;
    sec = Sector(x, y, r, s, a);
    return in;
}




void solve(int n) {
    start = std::chrono::high_resolution_clock::now();
    std::vector<Sector> vec(n);
    std::vector <double> net;
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
        //good_test >> vec[i];
    }

    double step = 0.35;
    double ans = 0;

    for (double j = -200; j <= 200; j += step)  {
        ans += get_adapt_simp(j, j + step, vec);
        //std::cout << j  << " " << ans << '\n';
    }


    std::cout << ans << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << std::fixed << std::setprecision(7);
    //solve(1);
    int n = 0;
    while(std::cin >> n) {
        solve(n);
    }
}