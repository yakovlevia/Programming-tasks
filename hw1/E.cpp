#include <iostream>
#include <vector>
#include <string>

int solve(std::string &str, int l, int r, int flag, char depth) {
    if (l == r) {
        if (depth == str[r]) return 0;
        else return 1;
    }
    if (flag == 0) {
        int mid = (l + r) / 2;
        int cnt = 0;
        for (int i = l; i <= mid; i++){
            if (str[i] != depth) cnt++;
        }
        return cnt + std::min(solve(str, mid + 1, r, 0, depth + 1), solve(str, mid + 1, r, 1, depth + 1));
    }
    else {
        int mid = (l + r) / 2;
        int cnt = 0;
        for (int i = mid + 1; i <= r; i++){
            if (str[i] != depth) cnt++;
        }
        return cnt + std::min(solve(str, l, mid, 0, depth + 1), solve(str, l, mid, 1, depth + 1));
    }
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::string str;
        std::cin >> str;
        int res = std::min(solve(str, 0, n - 1, 0, 'a'), solve(str, 0, n - 1, 1, 'a'));
        std::cout << res << '\n';
    }
    return 0;
}

/* Mon Sep 25 2023 20:30:38 GMT+0300 (Moscow Standard Time) */
