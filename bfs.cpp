#include <bits/stdc++.h>
#define int long long
using namespace std;

// 114271

vector <vector <int>> g;
int n, m;
vector <vector <int>> d;


vector <int> bfs(int v) {
    queue <int> q;
    q.push(v);
    vector <char> used(n);
    vector <int> d(n);
    used[v] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i=0; i<g[v].size(); ++i) {
            int to = g[v][i];
            if (!used[to]) {
                used[to] = 1;
                q.push (to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d;
}


signed main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int q;
	srand(42);
	cin >> n >> m >> q;
	g.resize(n);
	for (int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
	}
	set <int> ss;
	int max_col = min(n, 100ll);
	while (ss.size() < max_col){
        ss.insert(rand() % n);
    }
    vector <vector <int>> distance(max_col);
    int tt = 0;
    for (auto qq : ss){
        distance[tt] = bfs(qq);
        tt++;
    }
    for (int i = 0; i < q; i++){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        int ans = 1e7;
        for (int j = 0; j < max_col; j++){
            ans = min(ans, distance[j][x] + distance[j][y]);
        }
        cout << ans << '\n';
    }
}