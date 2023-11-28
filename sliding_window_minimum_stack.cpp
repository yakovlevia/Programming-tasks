#include <iostream>
#include <vector>
#include <climits>

// 756

int main() {
        n, m;
    std::cin >> n >> m;
    std::vector <std::pair<   ,    >> stack[2];
    for (int i = 0; i < n; i++) {
            a;
        std::cin >> a;
        if (!stack[0].empty()) stack[0].push_back({a, std::min(a, stack[0].back().second)});
        else stack[0].push_back({a, a});
        if (i == m - 1) {
            std::cout << stack[0].back().second << "\n";
        }
        if (i >= m) {
            if (stack[1].empty()) {
                stack[1].push_back({stack[0].back().first, stack[0].back().first});
                stack[0].pop_back();
                while (!stack[0].empty()) {
                    stack[1].push_back({stack[0].back().first, std::min(stack[1].back().second, stack[0].back().first)});
                    stack[0].pop_back();
                }
            }
            stack[1].pop_back();
                mn =  _ _MAX;
            if (!stack[0].empty()) mn = stack[0].back().second;
            if (!stack[1].empty()) mn = std::min(mn, stack[1].back().second);
            std::cout << mn << "\n";
        }
    }
    return 0;
}