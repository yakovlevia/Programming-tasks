#include <bits/stdc++.h>
#define int long long
using namespace std;

double dist(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1- y2);
}

signed main(){
    std::mt19937 rnd(139251);
    int n;
    std::cin >> n;
    std::vector <std::vector <double>> arr(n, vector <double> (3));
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }

    long long mx = rnd.max();
    long long cnt = 0;

    for (int i = 0; i < 1000000; i++) {
        double x = (rnd() / double(mx));
        double y = (rnd() / double(mx));

        //std::cout << x << " " << y << std::endl;

        for (int j = 0; j < n; j++) {
            if (dist(x, y, arr[j][0], arr[j][1]) <= arr[j][2] * arr[j][2]){
                cnt++;
                break;
            }
        }
    }
    std::cout << cnt / 10000.0;
    return 0;
}