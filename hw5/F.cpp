#include <bits/stdc++.h>

typedef long long ll;

ll zeros_cnt = 0;

struct Edge{
    ll w;
    int a;
    int b;
};

struct DSU{

    std::vector <int> parent;
    std::vector <int> rank;
    std::vector <int> size;

    void init(int n) {
        parent.resize(n, -1);
        rank.resize(n, -1);
        size.resize(n, -1);
    }

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
} zeros;

void bfs(int vv, std::vector <std::set<int>> &g, std::set<int> &vert) {
    if (vert.find(vv) == vert.end()) {
        return;
    } 

    std::queue<int> my_q;
    my_q.push(vv);

    while(!my_q.empty()) {
        int v = my_q.front();
        my_q.pop();
        std::vector <int> to_del;
        for (auto &q: vert) {
            if (g[v].find(q) == g[v].end()) {
                if (zeros.find_root(q) == zeros.find_root(v)) continue;
                to_del.push_back(q);
                zeros.union_sets(q, v);
                my_q.push(q);
                zeros_cnt++;
            }
        }

        for (auto &q : to_del) {
            vert.erase(q);
        }
    }   
}

bool cmp(Edge &a, Edge &b) {
    return a.w < b.w;
}

signed main() {
    int n, m;
    std::cin >> n >> m;
    std::vector <Edge> edges(m);
    std::vector <std::set<int>> g(n);
    ll my_xor = 0;
    ll my_ans = 0; 
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        std::cin >> a >> b >> c;
        a--;
        b--;
        edges[i] = {c, a, b};
        my_xor ^= c;
        g[a].insert(b);
        g[b].insert(a);
    }
    
    sort(edges.begin(), edges.end(), cmp);
    std::set<int> vert;
    zeros.init(n);
    for (int i = 0; i < n; i++) {
        vert.insert(i);
        zeros.make_set(i);
    }

    for (int i = 0; i < n; i++) {
        bfs(i, g, vert);
    }


    ll edge_to_add = my_xor;
    if (zeros_cnt < 1ll * n * (n - 1) / 2 - m) {
        edge_to_add = 0;
    }

    DSU new_vert;
    new_vert.init(n);
    for (int i = 0; i < n; i++) {
        new_vert.make_set(i);
    }

    for (auto &[w, a, b] : edges) {
        if (zeros.find_root(a) != zeros.find_root(b)) {
            new_vert.union_sets(a, b);
            zeros.union_sets(a, b);
            my_ans += w;

        }
        else if (new_vert.find_root(a) != new_vert.find_root(b)) {
            edge_to_add = std::min(edge_to_add, w);
        }
    }

    my_ans += edge_to_add;
    std::cout << my_ans;

}