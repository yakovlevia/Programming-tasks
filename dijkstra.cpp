#include <bits/stdc++.h>
#define int long long
using namespace std;

// 114444

int INF = 1e16;
int n, m;

struct Edge{
    int v;
    int w;
    int id;
};

vector <int> bad_edges;

void dijkstra(int s, vector <int> &d, vector <vector <Edge>> &g){
	vector <char> used(n);
	vector <int> id(n);
	d[s] = 0;
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j){
			if (!used[j] && (v == -1 || d[j] < d[v])){
				v = j;
			}
		}
		if (d[v] == INF) break;
		used[v] = 1;
		for (int j = 0; j < (int)g[v].size(); ++j) {
			int to = g[v][j].v, len = g[v][j].w;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				id[to] = g[v][j].id;
			}
		}
	}
	for (int i = 0; i < n; i++){
        if (i != s) bad_edges.push_back(id[i]);
	}
}


int check(vector <vector <Edge>> &g, int id, int s, int f){
	vector <char> used(n, 0);
	vector <int> d(n, INF);
	d[s] = 0;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j){
			if (!used[j] && (v == -1 || d[j] < d[v])){
				v = j;
			}
		}
		if (d[v] == INF) break;
		used[v] = 1;
		for (int j = 0; j < (int)g[v].size(); ++j) {
            if (id == g[v][j].id) continue;
			int to = g[v][j].v, len = g[v][j].w;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
			}
		}
	}
	return d[f];
}

signed main(){
    cin >> n >> m;
    vector <vector <Edge>> g(n);
    vector <vector <Edge>> gr(n);
    vector <int> dist_s(n, INF);
    vector <int> dist_f(n, INF);
    vector <int> dist_s_r(n, INF);
    vector <int> dist_f_r(n, INF);
    vector <int> cost(m);
    vector <int> weight(m);
    vector <pair <int, int>> edges(m);
    vector <int> check_edge(m, 0);
    for (int i = 0; i < m; i++){
        int x, y, c;
        cin >> x >> y >> c >> cost[i];
        g[x - 1].push_back({y - 1, c, i});
        gr[y - 1].push_back({x - 1, c, i});
        edges[i] = {x - 1, y - 1};
        weight[i] = c;
    }
    dijkstra(0, dist_s, g);
    dijkstra(n - 1, dist_f, g);
    dijkstra(0, dist_s_r, gr);
    dijkstra(n - 1, dist_f_r, gr);
    int min_ans = INF;
    min_ans = min(min_ans, dist_s[n - 1] + dist_f[0]);
    for (int i = 0; i < bad_edges.size(); i++){
        check_edge[bad_edges[i]] = 1;
    }
    for (int i = 0; i < m; i++){
        int cur_sum = cost[i];
        if (check_edge[i] == 0){
            cur_sum += min(dist_s[edges[i].second] + dist_f_r[edges[i].first] + weight[i], dist_s[n - 1]) + min(dist_s_r[edges[i].first] + dist_f[edges[i].second] + weight[i], dist_f[0]);
            min_ans = min(min_ans, cur_sum);
        }
        else {
            g[edges[i].second].push_back({edges[i].first, weight[i], -1});
            cur_sum += check(g, i, 0, n - 1);
            cur_sum += check(g, i, n - 1, 0);
            g[edges[i].second].pop_back();
            min_ans = min(min_ans, cur_sum);
        }

    }
    if (min_ans >= INF) {
        cout << -1;
        return 0;
    }
    cout << min_ans;
}