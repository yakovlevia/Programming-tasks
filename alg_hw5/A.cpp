#include <bits/stdc++.h>

void dijkstra(int s, std::vector <int> &d, std::vector<int> &p, std::vector <std::vector <std::pair<int, int>>> &g){
	d[s] = 0;
    std::set<std::pair<int, int>> q;
    q.insert({0, s});
    p[s] = s;
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [u, w] : g[v]) {
            if (d[u] == -1 || d[u] > d[v] + w) {
                q.erase({d[u], u});
                d[u] = d[v] + w;
                p[u] = v;
                q.insert({d[u], u});
            }
        }
    }
}

void get_par(int s, int f, std::vector<int> &parent) {
    std::vector <int> ans;
    int v = f;
    while(v != s) {
        ans.push_back(v);
        v = parent[v];
    }
    ans.push_back(v);

    std::cout << ans.size() << "\n";

    for (int i = ans.size() - 1; i >= 0; i--) {
        std::cout << ans[i] << " ";
    }
}

int main() {
    int n, m, s, f;
    std::cin >> n >> m >> s >> f;
    std::vector<std::vector<std::pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    
    std::vector<int> dist(n, -1);
    std::vector<int> parent(n, -1);

    dijkstra(s, dist, parent, g);
    for (int i = 0; i < n; i++) {
        std::cout << dist[i] << " ";
    }
    std::cout << "\n";
    if (dist[f] == -1) {
        std::cout << -1;
        return 0;
    }
    get_par(s, f, parent);
    return 0;
}