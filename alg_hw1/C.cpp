#include <iostream>

long long bin_pow(long long n, long long p, long long m) {
    if (p == 1) {
        return n % m;
    }
    else if (p % 2 == 0) {
        long long tmp = bin_pow(n, p / 2, m);
        return (tmp * tmp) % m;
    }
    else {
        return ((n % m) * bin_pow(n, p - 1, m)) % m;
    }
}

int main() {
    long long n, m, p;
    std::cin >> n >> m >> p;
    std::cout << bin_pow(n, p, m);
    return 0;
}
