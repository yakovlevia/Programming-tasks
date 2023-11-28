#include <bits/stdc++.h>

const int INF = 10000000;

struct Edge{
    int v;
    int w;
    int cnt;
};

void dijkstra(int s, std::vector <int> &d, std::vector <std::vector <Edge>> &g, int max_w = -1){
	d[s] = 0;
    std::set<std::pair<int, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [u, w, cnt] : g[v]) {
            if (cnt < max_w) continue;
            if (d[u] == -1 || d[u] > d[v] + w) {
                q.erase({d[u], u});
                d[u] = d[v] + w;
                q.insert({d[u], u});
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        d = (d - 3e6) / 100;
        a--;
        b--;
        g[a].push_back({b, c, d});
        g[b].push_back({a, c, d});
    }
    
    int l = 0;
    int r = INF + 1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;

        std::vector<int> dist(n, -1);

        dijkstra(0, dist, g, mid);
        //std::cout << dist[n - 1] << " " << mid << "\n";
        if (dist[n - 1] == -1 || dist[n - 1] > 1440) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    std::cout << r - 1;
   
}