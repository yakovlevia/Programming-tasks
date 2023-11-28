#include <bits/stdc++.h>

//3558

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
    int n, m;
    std::cin >> n >> m;
    parent.resize(n, 0);
    rank.resize(n, 0);

    std::vector <std::pair<int, int>> edge;
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        edge.push_back({a - 1, b - 1});
    }

    int k;
    std::cin >> k;
    std::vector<int> net(k);
    std::vector<int> nnet(m, 0);

    for (int i = 0; i < k; i++) {
        std::cin >> net[i];
        net[i] = net[i] - 1;
        nnet[net[i]] = 1;

    }
    for (int i = 0; i < n; i++) {
        make_set(i);
    }

    int ans = n;
    std::vector <int> aans(k);

    for (int i = 0; i < edge.size(); i++) {
        if (!nnet[i]) {
            if (find_root(edge[i].first) != find_root(edge[i].second)) {
                ans--;
                union_sets(edge[i].first, edge[i].second);
            }
        }
    }

    for (int i = k - 1; i >= 0; i--) {

        int pos = net[i];
        aans[i] = ans;
        if (find_root(edge[pos].first) != find_root(edge[pos].second)) {
            ans--;
            union_sets(edge[pos].first, edge[pos].second);
        }
    }

    for (auto q : aans) {
        std::cout << q << " ";
    }
}