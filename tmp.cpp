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

void my_sort(std::vector <std::pair<int, std::pair<int,  int>>> &g) {
    std::vector <std::vector <std::pair<int, int>>> tmp(1001);
    
    for (auto &q : g) {
        tmp[q.first].push_back(q.second);
    }

    int cnt = 0;
    for (int i = 0; i < tmp.size(); i++) {
        for (auto &q : tmp[i]) {
            g[cnt] = {i, q};
            cnt++;
        }
    }
}

void dfs(int fr, int v, std::vector <std::vector <int>> &dist, std::vector <std::vector <std::pair<int, int>>> &g) {
    if (fr == v) {
        dist[fr][v] = 0;
    }
    for (auto q : g[v]) {
        if (dist[fr][q.first] == -1) {
            dist[fr][q.first] = std::max(q.second, dist[fr][v]);
            dfs(fr, q.first, dist, g);
        }
    }
}

std::pair<int, int> get_ans(int n, int m, std::vector <std::pair<int, std::pair<int,  int>>> test) {
    std::vector <std::pair<int, std::pair<int,  int>>> g;
    //int n, m;
    //std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        //std::cin >> a >> b >> c;
        a = test[i].second.first;
        b = test[i].second.second;
        c = test[i].first;
        // a--;
        // b--;
        g.push_back({c, {std::min(a, b), std::max(a, b)}});
    }
    
    my_sort(g);

    std::vector<int> res;
    int ans = get_ans(g, n, m, res, -1);
    
    std::vector <std::vector <std::pair<int, int>>> ost(n);
    for (auto &q : res) {
        ost[g[q].second.first].push_back({g[q].second.second, g[q].first});
        ost[g[q].second.second].push_back({g[q].second.first, g[q].first});
    }
    
    std::vector <std::vector <int>> dist(n, std::vector <int> (n, -1));

    for (int i = 0; i < n; i++) {
        dfs(i, i, dist, ost);
    }
    

    int t_ans = INT_MAX;

    int cnt = 0;
    for (int i = 0; i < g.size(); i++) {
        if (cnt < res.size() && res[cnt] == i) {
            cnt++;
            continue;
        }
        if (dist[g[i].second.first][g[i].second.second] != -1) t_ans = std::min(t_ans, ans - dist[g[i].second.first][g[i].second.second] + g[i].first);
    }

    if (t_ans == INT_MAX) t_ans = -1;
    //std::cout << "Cost: " << ans << "\n";
    //std::cout << "Cost: " << t_ans << "\n";
    return {ans, t_ans};
}










int find_set_1(int v, std::vector<int> &parents) {
    if (v == parents[v]) {
        return parents[v];
    }
    parents[v] = find_set_1(parents[v], parents);
    return parents[v];
}

bool union_sets_1(int a, int b, std::vector<int> &parents, std::vector<int> &sizes) {
	a = find_set_1 (a, parents);
	b = find_set_1 (b, parents);
	if (a != b) {
		if (sizes[a] < sizes[b]) {
            std::swap (a, b);
        }
        parents[b] = a;
        sizes[a] += sizes[b];
        return false;
    }
    return true;
}

std::pair<int, int> get_ans_1(int N, int M, std::vector <std::pair<int, std::pair<int,  int>>> &edjes) {
    std::vector<bool> min_ostov(M, false);
    std::vector<int> parents(N);
    std::vector<int> sizes(N, 1);
    for (int i = 0; i < N; i++) {
        parents[i] = i;
    }
    std::sort(edjes.begin(), edjes.end());

    long long min_weight = 0;
    for (int i = 0; i < M; i++) {
        int a = edjes[i].second.first;
        int b = edjes[i].second.second;
        int w = edjes[i].first;
        if (!union_sets_1(a, b, parents, sizes)) {
            min_weight += w;
            min_ostov[i] = true;
        }
    }

    long long current_min = 0;
    long long prev_min = -1;
    for (int j = 0; j < N; j++) {
        bool is_same = true;
        current_min = 0;
        for (int i = 0; i < N; i++) {
            parents[i] = i;
            sizes[i] = 1;
        }
        std::vector<std::pair<int, int>> current_neighbours;
        std::vector<int> current_neighbours_indexes;
        for (int i = 0; i < M; i++) {
            int a = edjes[i].second.first;
            int b = edjes[i].second.second;
            int w = edjes[i].first;
            if (a != j && b != j) {
                if (!union_sets_1(a, b, parents, sizes)) {
                    current_min += w;
                    if (!min_ostov[i]) {
                        is_same = false;
                    }
                }
            } else if (a == j) {
                current_neighbours.push_back(std::make_pair(w, b));
                current_neighbours_indexes.push_back(i);
            } else {
                current_neighbours.push_back(std::make_pair(w, a));
                current_neighbours_indexes.push_back(i);
            }
        }
        
        bool can_build = true;
        for (int i = 0; i < current_neighbours.size(); i++) {
            for (int j = i + 1; j < current_neighbours.size(); j++) {
                int a = find_set_1(current_neighbours[i].second, parents);
                int b = find_set_1(current_neighbours[j].second, parents);
                if (a != b) {
                    can_build = false;
                }
            }
        }

        if (can_build) {
            for (int i = 0; i < current_neighbours.size(); i++) {
                if (!is_same || !min_ostov[current_neighbours_indexes[i]]) {
                    current_min += current_neighbours[i].first;
                    if (prev_min != -1) {
                        if (current_min < prev_min) {
                            prev_min = current_min;
                        }
                    } else {
                        prev_min = current_min;
                    }
                    break;
                }
            }
        }
    }

    std::pair<int, int> ans;
    ans.first = min_weight;
    ans.second = prev_min;
    return ans;
}






std::ofstream my_ans("myans.txt");
int main() {
    srand(time(0));
    int n, m;
    int cnr = 0;
    while (cnr == 0) {
        n = 1000;
        m = n * (n - 1) / 2;
        cnr++;
        std::vector<std::pair<int, int>> tmp;


        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                tmp.push_back({i, j});
            }
        }
        std::random_shuffle(tmp.begin(), tmp.end());
        std::vector <std::pair<int, std::pair<int,  int>>> test(m);

        for (int i = 0; i < m; i++) {
            test[i] = {rand() % 10, tmp[i]};
        }

        std::pair<int,int> ans1 = get_ans(n, m, test);
        std::cout << cnr << "\n";
        if (ans1.first == -1) continue;
        std::pair<int,int> ans2 = get_ans(n, m, test);

        if (ans1 == ans2) {
           my_ans << n << " " << m << "\n";
            for (int i = 0; i < m; i++) {
                my_ans << test[i].second.first + 1 << " " << test[i].second.second + 1 << " " << test[i].first << "\n";
            }
            my_ans << "ans: " << ans1.first << " " << ans1.second << "\n";
            my_ans << "bad: " << ans2.first << " " << ans2.second << "\n";
            break;

        }

    }

}