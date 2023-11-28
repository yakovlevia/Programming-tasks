#include <iostream>
#include <vector>

void merge_sort(std::vector <int> &arr, int l, int r) {
    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    std::vector <int> left(mid + 1);
    std::vector <int> right(r - mid);

    for (int i = 0; i <= mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid + 1; i <= r; i++) {
        right[i - mid - 1] = arr[i];
    }

    merge_sort(left, 0, mid);
    merge_sort(right, 0, r - mid - 1);

    int cnt_l, cnt_r;
    cnt_l = cnt_r = 0;
    for (int i = 0; i <= r; i++) {
        if (cnt_l > mid) {
            arr[i] = right[cnt_r];
            cnt_r++;
        }
        else if (cnt_r > r - mid - 1) {
            arr[i] = left[cnt_l];
            cnt_l++;
        }
        else if (left[cnt_l] > right[cnt_r]) {
            arr[i] = left[cnt_l];
            cnt_l++;
        }
        else {
            arr[i] = right[cnt_r];
            cnt_r++;
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std:: cin >> arr[i];
    }

    merge_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std:: cout << arr[i] << " ";
    }

    return 0;
}
