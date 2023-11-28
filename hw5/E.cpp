#include <bits/stdc++.h>

std::vector <int> parent;
std::vector <int> rank;
std::vector <int> size;

void make_set(int v) {
	parent[v] = v;
	rank[v] = 0;
    size[v] = 1;
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
        size[a] += size[b];
		if (rank[a] == rank[b]) {
			rank[a]++;
        }
	}
}

int main() {
    int n, m;
    std::cin >> n >> m;
    parent.resize(n, -1);
    rank.resize(n, -1);
    size.resize(n, -1);
    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
    }

    std::vector<int> edge(n, 0);
    std::set <int> comp;

    for (int i = 0; i < n; i++) {
        make_set(i);
        
        std::set<int> new_comp;
        std::map <int, int> edge;

        for (auto &q : g[i]) {
            if (q > i) break;
            edge[find_root(q)]++;
        }

        int parr = -1;

        for (auto &q : comp) {
            if (edge[q] < size[q]) {
                union_sets(i, q);
                parr = find_root(i);
            }
            else {
                new_comp.insert(q);
            }
        }

        if (parr == -1) {
            comp.insert(i);
        }
        else {
            new_comp.insert(parr);
            comp = new_comp;
        }

    }

    std::cout << comp.size() - 1 << "\n";

}