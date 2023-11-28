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

int main() {
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
    std::sort(g.begin(), g.end());


    std::vector<int> res;
    int ans = get_ans(g, n, m, res, -1);
    int t_ans = INT_MAX;
    for (int i = 0; i < res.size(); i++) {
        int aa = get_ans(g, n, m, res, res[i]);
        //std::cout << "aa " << aa << "\n";
        if (aa != -1) t_ans = std::min(t_ans, aa);
    }
    if (t_ans == INT_MAX) t_ans = -1;
    std::cout << "Cost: " << ans << "\n";
    std::cout << "Cost: " << t_ans << "\n";
    
}