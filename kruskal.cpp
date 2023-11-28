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

int main() {
    std::vector <std::pair<int, std::pair<int,  int>>> g;
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        g.push_back({c, {a, b}});
    }

    unsigned     ans = 0;
    std::vector<std::pair<int, int>> res;

    std::sort(g.begin(), g.end());
    parent.resize(n);
    rank.resize(n);

    for (int i = 0; i < n; i++){
        make_set(i);
    }

    for (int i = 0; i < m; i++) {
        int a = g[i].second.first,  b = g[i].second.second;
        unsigned     l = g[i].first;
        if (find_root(a) != find_root(b)) {
            ans += l;
            res.push_back(g[i].second);
            union_sets(a, b);
        }
    }

    for (int i = 0; i < n - 1; i++) {
        if (find_root(i) != find_root(i + 1)) {
            std::cout << "NON-CONNECTED\n";
            return 0;
        }
    }
    std::cout << ans;
}