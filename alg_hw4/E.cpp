#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx")
typedef long long ll;

std::vector <int> parent;
std::vector <int> rank;
int k;

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
 
int union_sets(int a, int b) {
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
        return 0;
	}
    else {
        return 1;
    }
}

int fun(int mid) {
    for (int i = 1; i <= mid; i++) {
        make_set(i);
    }

    for (int i = 1; i <= mid; i++) {
        int a = i;
        int ak = (a * (long long)(a)) % k;

        int kb = k - ak;
        for (int j = kb; j <= mid; j += k) {
            if (a >= j && ((1ll * a * a + j) % k == (1ll * j * j + a) % k)) continue;
            if (union_sets(a, j)) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    std::cin >> k;
    parent.resize(3 * k + 1, 0);
    rank.resize(3 * k + 1, 0);

    int r = 3 * k + 1;
    int l = 1;
    

    // for (int j = 1; j < r; j++) {
    //     if (fun(j)) {
    //         std::cout << j;
    //         return 0;
    //     }
    // }

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (fun(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }
    std::cout << l + 1 << "\n";
    
}