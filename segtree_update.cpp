#include <bits/stdc++.h>
#define int    long long
using namespace std;

// 753

int INF = 1e13;

struct SegTree{
    struct Node {
        int max;
        int col;
    };

    vector<Node> tree;
    int sz;

    SegTree(int n) {
        sz = n;
        tree.resize(4 * sz, {0, -1});
    }

    void push(int v, int lx, int rx) {
        if (tree[v].col == -1) {
            return;
        }
        tree[v].max = tree[v].col;
        if (rx - lx > 1) {
            tree[2 * v + 1].col = tree[v].col;
            tree[2 * v + 2].col = tree[v].col;
        }
        tree[v].col = -1;
    }

    int get_max(int l, int r, int v, int tl, int tr) {
        push(v, tl, tr);
        if (tl >= r || tr <= l) {
            return -1;
        }
        if (tl >= l && tr <= r) {
            return tree[v].max;
        }
        int m = (tl + tr) / 2;
        return max(get_max(l, r, 2 * v + 1, tl, m), get_max(l, r, 2 * v + 2, m, tr));
    }

    int get_max(int l, int r) {
        return get_max(l, r, 0, 0, sz);
    }

    int get(int i) {
        return get_max(i, i + 1);
    }

    void update(int l, int r, int val, int v, int tl, int tr) {
        push(v, tl, tr);
        if (tl >= r || tr <= l) {
            return;
        }
        if (tl >= l && tr <= r) {
            tree[v].col = val;
            push(v, tl, tr);
            return;
        }
        int m = (tl + tr) / 2;
        update(l, r, val, 2 * v + 1, tl, m);
        update(l, r, val, 2 * v + 2, m, tr);
        tree[v].max = max(tree[2 * v + 1].max, tree[2 * v + 2].max);
    }

    void update(int l, int r, int val) {
        update(l, r, val, 0, 0, sz);
    }


};


signed main(){
    int n, m;
    cin >> n >> m;
    SegTree tree(n);
    vector <int> tmp(n);
    for (int i = 1; i <= n; ++i) {
        tmp.push_back(i);
    }
    vector<int> left(n + 1);
    vector<int> right(n + 1);
    for (int q = 0; q < m; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            if (tree.get_max(l, r) == 0) {
                cout << "1\n";
                int g = tmp.back();
                tmp.pop_back();
                left[g] = l;
                right[g] = r;
                tree.update(l, r, g);
            }
            else {
                cout << "0\n";
            }
        }
        else {
            int p;
            cin >> p;
            --p;
            int g = tree.get(p);
            if (g == 0) {
                cout << "0 0\n";
            }
            else {
                cout << left[g] + 1 << " " << right[g] << "\n";
                tree.update(left[g], right[g], 0);
                tmp.push_back(g);
            }
        }
    }
}