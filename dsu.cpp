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
    std::string str;
    while (std::cin >> str) {
        if (str == "RESET") {
            int k;
            std::cin >> k;
            parent.resize(k, 0);
            rank.resize(k, 0);
            for (int i = 0; i < k; i++) {
                make_set(i);
            }
            std::cout << "RESET DONE\n";
        }
        else if (str == "JOIN"){
            int a, b;
            std::cin >> a >> b;
            if (find_root(a) == find_root(b)) {
                std::cout << "ALREADY " << a << " " << b << "\n";
            }
            else {
                union_sets(a, b);
            }
        }
        else if (str == "CHECK") {
            int a, b;
            std::cin >> a >> b;
            if (find_root(a) == find_root(b)) {
                std::cout << "YES\n";
            }
            else {
                std::cout << "NO\n";
            }
        }

    }
}