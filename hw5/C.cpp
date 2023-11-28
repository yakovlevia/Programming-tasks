#include <bits/stdc++.h>

const int INF = 10000000;

struct Edge{
    int v;
    int sending_t;
    int arrival_t;
};



void dijkstra(int s, std::vector <int> &d, std::vector <std::vector <Edge>> &g, int max_w = -1){
	d[s] = 0;
    std::set<std::pair<int, int>> q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        int t = q.begin()->first;
        q.erase(q.begin());
        for (auto [u, st, at] : g[v]) {
            if (t > st) continue;
            if (d[u] == -1 || d[u] > at) {
                q.erase({d[u], u});
                d[u] = at;
                q.insert({d[u], u});
            }
        }
    }
}

int main() {
    int n, m, s, f;
    std::cin >> n >> s >> f >> m;
    s--;
    f--;
    std::vector<std::vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        std::cin >> a >> c >> b >> d;
        a--;
        b--;
        g[a].push_back({b, c, d});
    }
    
    std::vector<int> dist(n, -1);
    dijkstra(s, dist, g);  

   

    std::cout << dist[f];
   
}