#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std:: cin >> arr[i];
    }

    for (int i = 1; i < n; i++) {
        int k = i;
        while (k > 0) {
            if (arr[k - 1] < arr[k]) {
                std::swap(arr[k - 1],  arr[k]);
                k--;
            }
            else {
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std:: cout << arr[i] << " ";
    }

    return 0;
}
