#include <bits/stdc++.h>

//3558

int main() {
    int n, m;
    std::cin >> n;

    std::vector <long long> pref(n + 1, 0), que(n);

    for (int i = 0; i < n; i++) {
        long long a;
        std::cin >> a;
        pref[i + 1] = pref[i] + a;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> que[i];
        que[i]--;
    }

    std::set <int> pos;
    for (int i = 0; i < n; i++) {
        pos.insert(i);
    }

    long long ans = 0;
    std::vector <long long> aans(n);
    
    for (int i = n - 1; i >= 0; i--) {
        aans[i] = ans;
        pos.erase(que[i]);
        int l, r;
        auto ppos = pos.upper_bound(que[i]);
        if (ppos == pos.end()) {
            r = n - 1;
        }
        else {
            r = *ppos - 1;
        }
        if (ppos == pos.begin()) {
            l = 0;
        }
        else {
            ppos--;
            l = *ppos + 1;
        }
        //std::cout << l << " " << r << "\n";
        
        ans = std::max(ans, pref[r + 1] - pref[l]);

    } 


    for (auto q : aans) {
        std::cout << q << "\n";
    }
}
/* Sat Nov 18 2023 22:31:49 GMT+0300 (Moscow Standard Time) */
