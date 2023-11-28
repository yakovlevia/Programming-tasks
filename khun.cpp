#include <bits/stdc++.h>
#define int long long

// 1932

using namespace std;

using pii = pair<int, int>;
using pll = pair<   ,    >;
using ll =    ;
using ull = unsigned    ;
int INF = 1e9 + 100;
ll LL_INF = 1e18;



istream &operator >> (istream &in, pii &x){
    in >> x.first >> x.second;
    return in;
}

ostream &operator >> (ostream &out, pii &x){
    out << x.first << " " << x.second;
    return out;
}

template <typename T>

istream &operator >> (istream &in, vector <T> &vec){
    for (int i = 0; i < vec.size(); i++){
        in >> vec[i];
    }
    return in;
}

template <typename T>

ostream &operator << (ostream& out, vector <T> &vec){
    //out << vec.size() << '\n';
    for (int i = 0; i < vec.size(); i++){
        out << vec[i] << " ";
    }
    out << '\n';
    return out;
}


void sleep1(double t){
    clock_t s = clock();
    while (double(clock() - s) / CLOCKS_PER_SEC < t){}
}

int n, m, k;

char g[205][205];
char used[205];
int mt[205];

bool try_kuhn(int v){
    if (used[v]) return false;
    used[v] = 1;
    for (int i = 0; i < n + m - k; i++){
        if (g[v][i] == 1){
            if (mt[i] == -1 || try_kuhn(mt[i])){
                mt[i] = v;
                return true;
            }
        }
    }
    return false;
}

signed main (){
    cin >> n >> m >> k;
    memset(g, 0, sizeof(g));
    for (int i = 0; i < n + m - k; i++){
        for (int j = 0; j < n + m - k; j++){
            g[i][j] = 1;
        }
    }
    for (int i = n; i < n + m - k; i++){
        for (int j = m; j < n + m - k; j++){
            g[i][j] = 0;
        }
    }
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        if (x > y) swap(x, y);
        g[x][y - n] = 0;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++){
        int x;
        cin >> x;
        x--;
        if (x < n){
            for (int j = m; j < n + m - k; j++){
                g[x][j] = 0;
            }
        }
        else {
            for (int j = n; j < n + m - k; j++){
                g[j][x - n] = 0;
            }
        }
    }
    memset(mt, -1, sizeof(mt));
    bool fl = 1;
    for (int i = 0; i < n + m - k; i++){
        memset(used, 0, sizeof(used));
        if (!try_kuhn(i)){
            fl = 0;
        }
    }
    if (!fl){
        cout << "NO";
    }
    else {
        cout << "YES" << endl;
        for (int i = 0; i < m; i++){
            if (mt[i] < n){
                cout << mt[i] + 1 << " " << i + n + 1 << endl;
            }
        }
    }
}