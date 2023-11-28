#include <bits/stdc++.h>

int main(){
    int m;
    std::cin >> m;
    for (int n = 2; n <= m + 1; n++) {
        for (int j = 1; j < n; j++){
            for (int k = 0; k < j; k++) {
                std::cout << "? " << k + 1 << " " << j + 1 << '\n';
                //std::cout << "? " << k + 1 << " " << j + 1 << '\n';
            }
        }
        std::cout << " ! " << n / 2 << " " << n / 2 + 1 << '\n';
    }
    return 0;
}