#include <bits/stdc++.h>

std::vector <int> parent;
std::vector <int> rank;

void make_set(int v) {
	parent[v] = v;
	rank[v] = 0;
}
 
int find_root(int v) {
	if (v == parent[v]) {
		return v;
    }
	return parent[v] = find_root(parent[v]);
}
 
void union_sets(int a, int b) {
	a = find_root(a);
	b = find_root(b);
	if (a != b) {
		if (rank[a] < rank[b]) {
			std::swap(a, b);
        }
		parent[b] = a;
		if (rank[a] == rank[b]) {
			rank[a]++;
        }
	}
}

int get_ans(std::vector <std::pair<int, std::pair<int,  int>>> &g, int n, int m, std::vector<int> &res, int k = -1) {
    unsigned ans = 0;
    parent.resize(n);
    if (k == -1) rank.resize(n);

    for (int i = 0; i < n; i++){
        make_set(i);
    }

    for (int i = 0; i < m; i++) {
        if (i == k) continue;
        int a = g[i].second.first,  b = g[i].second.second;
        unsigned l = g[i].first;
        if (find_root(a) != find_root(b)) {
            ans += l;
            if (k == -1) res.push_back(i);
            union_sets(a, b);
        }
    }
    
    for (int i = 0; i < n - 1; i++) {
        if (find_root(i) != find_root(i + 1)) {
            //std::cout << "NON-CONNECTED\n";
            return -1;
        }
    }

    return ans;
}

void my_sort(std::vector <std::pair<int, std::pair<int,  int>>> &g) {
    std::vector <std::vector <std::pair<int, int>>> tmp(1001);
    
    for (auto &q : g) {
        tmp[q.first].push_back(q.second);
    }

    int cnt = 0;
    for (int i = 0; i < tmp.size(); i++) {
        for (auto &q : tmp[i]) {
            g[cnt] = {i, q};
            cnt++;
        }
    }
}

void dfs(int fr, int v, std::vector <std::vector <int>> &dist, std::vector <std::vector <std::pair<int, int>>> &g) {
    if (fr == v) {
        dist[fr][v] = 0;
    }
    for (auto q : g[v]) {
        if (dist[fr][q.first] == -1) {
            dist[fr][q.first] = std::max(q.second, dist[fr][v]);
            dfs(fr, q.first, dist, g);
        }
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    std::vector <std::pair<int, std::pair<int,  int>>> g;
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        g.push_back({c, {std::min(a, b), std::max(a, b)}});
    }
    
    my_sort(g);

    std::vector<int> res;
    int ans = get_ans(g, n, m, res, -1);
    
    std::vector <std::vector <std::pair<int, int>>> ost(n);
    for (auto &q : res) {
        ost[g[q].second.first].push_back({g[q].second.second, g[q].first});
        ost[g[q].second.second].push_back({g[q].second.first, g[q].first});
    }
    
    std::vector <std::vector <int>> dist(n, std::vector <int> (n, -1));

    for (int i = 0; i < n; i++) {
        dfs(i, i, dist, ost);
    }
    

    int t_ans = INT_MAX;

    int cnt = 0;
    for (int i = 0; i < g.size(); i++) {
        if (cnt < res.size() && res[cnt] == i) {
            cnt++;
            continue;
        }
        if (dist[g[i].second.first][g[i].second.second] != -1) t_ans = std::min(t_ans, ans - dist[g[i].second.first][g[i].second.second] + g[i].first);
    }

    if (t_ans == INT_MAX) t_ans = -1;
    std::cout << "Cost: " << ans << "\n";
    std::cout << "Cost: " << t_ans << "\n";
    
}