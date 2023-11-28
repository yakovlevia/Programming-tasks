#include <bits/stdc++.h>

double EPS = 1e-12;

std::ifstream good_test("test.txt");
std::ifstream good_ans("ans.txt");
std::ofstream my_ans("myans.txt");

auto c_start = std::chrono::high_resolution_clock::now();
auto c_end = std::chrono::high_resolution_clock::now();

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


double g(double x, Sector &sec) {
    return sec.y - std::sqrt(sec.r * sec.r - std::pow(x - sec.x, 2));
}

double f(double x, Sector &sec) {
    return sec.y + std::sqrt(sec.r * sec.r - std::pow(x - sec.x, 2));
}

double get_int_adapt_g(double l, double r, Sector &cur) {
    l -= cur.x;
    r -= cur.x;

    if (l <= -cur.r) {
        l = - cur.r;
    }
    else if (l >= cur.r) {
        l = cur.r;
    }

    if (r <= -cur.r) {
        l = - cur.r;
    }

    else if (r >= cur.r) {
        r = cur.r;
    }

    double g = -cur.r * cur.r * std::asin(l / cur.r) + -l * std::sqrt(cur.r * cur.r - l * l);
    g /= 2;
    g += l * cur.y;

    double f = -cur.r * cur.r * std::asin(r / cur.r) + -r * std::sqrt(cur.r * cur.r - r * r);
    f /= 2;
    f += r * cur.y;
    return f - g;
}

double get_int_adapt_f(double l, double r, Sector &cur) {
    l -= cur.x;
    r -= cur.x;

    if (l <= -cur.r) {
        l = - cur.r;
    }
    else if (l >= cur.r) {
        l = cur.r;
    }

    double g = cur.r * cur.r * std::asin(l / cur.r) + l * std::sqrt(cur.r * cur.r - l * l);
    g /= 2;
    g += l * cur.y;

    if (r <= -cur.r) {
        l = - cur.r;
    }
    else if (r >= cur.r) {
        r = cur.r;
    }

    double f = cur.r * cur.r * std::asin(r / cur.r) + r * std::sqrt(cur.r * cur.r - r * r);
    f /= 2;
    f += r * cur.y;
    return f - g;
}

std::istream& operator >> (std::istream& in, Sector& sec) {
    double x, y, r, s, a;
    in >> x >> y >> r >> s >> a;
    sec = Sector(x, y, r, s, a);
    return in;
}

void check_rad(Sector &cur, double l, double r, std::vector <std::pair<double, int>> &lines) {
    double mid = (l + r) / 2;
    if (mid < cur.x - cur.r || mid > cur.x + cur.r) return;
    double val_up = f((l + r) / 2, cur) * (r - l);
    double val_down = g((l + r) / 2, cur) * (r - l);

    if (cur.s + cur.a >= 0 && cur.s + cur.a <= M_PI && cur.x1 <= mid && mid <= cur.x2) {
        lines.push_back({val_up, 1});
    }
    else if (cur.s + cur.a > M_PI && cur.s + cur.a < 2 * M_PI) {
        if (cur.s <= M_PI) {
            if (cur.x - cur.r < mid && mid < cur.x2) {
                lines.push_back({val_up, 1});
            }
            if (cur.x - cur.r < mid && mid < cur.x1) {
                lines.push_back({val_down, -1});
            }
        }
        else {
            if (cur.x2 < mid && mid < cur.x1) {
                lines.push_back({val_down, -1});
            }
        }
    }
    else if (cur.s + cur.a > 2 * M_PI && cur.s + cur.a < 3 * M_PI) {
        if (cur.s <= M_PI) {
            if (cur.x - cur.r < mid && mid < cur.x2) {
                lines.push_back({val_up, 1});
            }
            if (cur.x1 < mid && mid < cur.x + cur.r) {
                lines.push_back({val_up, 1});
            }
            lines.push_back({val_down, -1});
        }
        else if (M_PI < cur.s && cur.s < 2 * M_PI) {
            if (cur.x1 < mid && mid < cur.x + cur.r) {
                lines.push_back({val_up, 1});
            }
            if (cur.x2 < mid && mid < cur.x + cur.r) {
                lines.push_back({val_down, -1});
            }
        }
    }
    else if (cur.s + cur.a > 3 * M_PI && cur.s + cur.a < 4 * M_PI) {
        lines.push_back({val_up, 1});
        if (cur.x - cur.r < mid && mid < cur.x1) {
            lines.push_back({val_down, -1});
        }
        if (cur.x2 < mid && mid < cur.x + cur.r) {
            lines.push_back({val_down, -1});
        }
    }
}

void line1(Sector &cur, double l, double r, std::vector <std::pair<double, int>> &lines) {
    double mid = (l + r) / 2;
    if (cur.x1 > cur.x) {
        if (cur.x < mid && mid < cur.x1) {
            lines.push_back({(cur.y + (cur.y1 - cur.y) * ((mid - cur.x) / (cur.x1 - cur.x))) * (r - l), 1});
        }
    }
    else {
        if (cur.x1 < mid && mid < cur.x) {
            lines.push_back({(cur.y + (cur.y1 - cur.y) * ((mid - cur.x) / (cur.x1 - cur.x))) * (r - l), -1});
        }
    }
}

void line2(Sector &cur, double l, double r, std::vector <std::pair<double, int>> &lines) {
    double mid = (l + r) / 2;
    if (cur.x2 < cur.x) {
        if (cur.x2 < mid && mid < cur.x) {
            lines.push_back({(cur.y + (cur.y2 - cur.y) * ((mid - cur.x) / (cur.x2 - cur.x))) * (r - l), 1});
        }
    }
    else {
        if (cur.x < mid && mid < cur.x2) {
            lines.push_back({(cur.y + (cur.y2 - cur.y) * ((mid - cur.x) / (cur.x2 - cur.x))) * (r - l), -1});
        }
    }
}

void make_lines(std::vector <std::pair<double, int>> &lines, std::vector<Sector> &vec, double l, double r) {
    for (int i = 0; i < vec.size(); i++) {
        Sector cur = vec[i];
        double mid = (l + r) / 2;

        check_rad(cur, l, r, lines);
        line1(cur, l, r, lines);
        line2(cur, l, r, lines);
    }
}

double generate(double l, double r, std::vector<Sector> &vec) {
    std::vector <std::pair<double, int>> lines(0);
    make_lines(lines,vec, l, r);

    std::sort(lines.begin(), lines.end());

    int cnt = 0;
    double prev = 0;
    double res = 0;
    for (int i = 0; i < lines.size(); i++) {
        std::cout << lines[i].first << " " << lines[i].second << '\n';
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

double generate_2(double l, double r, std::vector<Sector> &vec, int h = 0) {
    int kk = 2;
    std::vector <double> ans(kk);
    double aans = generate(l, r, vec);
    double aans1 = aans;
    for (int j = 0; j < kk; j++) {
       double ll = l + j * (r - l) / kk; 
       double rr = l + (j + 1) * (r - l) / kk; 
       ans[j] = generate(ll, rr, vec);
       aans -= ans[j];
    }
    
    if (h < 10 && std::abs(aans) > 1e-7) {
        double t_ans = 0;
        for (int pp = 0; pp < kk; pp++) {
            double ll = l + pp * (r - l) / kk; 
            double rr = l + (pp + 1) * (r - l) / kk; 
            t_ans += generate_2(ll, rr, vec, h + 1);
        }

        return t_ans;
    }
    return aans1;
}

void solve(int n) {
    std::vector<Sector> vec(n);
    std::vector <double> net;
    for (int i = 0; i < n; i++) {
        //std::cin >> vec[i];
        good_test >> vec[i];

        net.push_back(vec[i].x);
        net.push_back(vec[i].x - vec[i].r);
        net.push_back(vec[i].x + vec[i].r);
        net.push_back(vec[i].x1);
        net.push_back(vec[i].x2);
    }
    c_start = std::chrono::high_resolution_clock::now();

    sort(net.begin(), net.end());
    double ans = 0;
    //std::cout << net.size() << "\n";
    double last = net[0];
    for (double j = 1; j < net.size(); j++)  {
        ans += generate(last, net[j], vec);
        last = net[j];
        std::cout << net[0] << " " << net[j] << " " << ans << "\n";
    }
    double errr;
    good_ans >> errr;
    my_ans << ans << " " << ans - errr << " " << (std::abs(ans - errr) <= 1e-6)<< "\n";
    // c_end = std::chrono::high_resolution_clock::now();
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(c_end - c_start).count() << "ms\n";
    std::cout << ans << "\n";
    exit(0);
}

int main() {

    std::cout << std::fixed << std::setprecision(8);
    my_ans << std::fixed << std::setprecision(8);
    
    int n = 0;
    while(good_test >> n) {
        solve(n);
    }
    // while(std::cin >> n) {
    //    solve(n);
    // }
}