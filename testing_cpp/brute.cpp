#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }

    std::sort(vec.begin(), vec.end());

    std::cout << n << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << vec[i] << " ";
    }
}