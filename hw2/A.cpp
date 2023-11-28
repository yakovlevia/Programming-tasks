#include <bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
//#define int long long

int BLOCK_SZ = 10000;

void update(std::vector <long long> &vec, int fl = 1) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > BLOCK_SZ - 1) {
            if (i != vec.size() - 1) {
                int k = vec[i] / BLOCK_SZ;
                vec[i + 1] += k;
                vec[i] -= BLOCK_SZ * k;

            }
            else {
                int k = vec[i] / BLOCK_SZ;
                vec.push_back(k);
                vec[i] -= BLOCK_SZ * k;
                break;
            }
        }
        else if (vec[i] < 0) {
            int k = (vec[i] - (BLOCK_SZ - 1)) / BLOCK_SZ;
            vec[i + 1] += k;
            vec[i] -= BLOCK_SZ * k;
        }
    }

    if (fl) {
        while (vec.size() > 1 && vec.back() == 0) {
            vec.pop_back();
        }
    }
}

void fill(std::vector <long long> &l, std::vector <long long> &r){
    while(l.size() < r.size()) {
        l.push_back(0);
    }

    while(r.size() < l.size()) {
        r.push_back(0);
    }
}

void minus(std::vector <long long> &l, std::vector <long long> &r) {
    fill(l, r);
    for (int i = 0; i < l.size(); i++) {
        l[i] -= r[i];
    }
    update(l);
}

void plus(std::vector <long long> &l, std::vector <long long> &r) {
    fill(l, r);
    for (int i = 0; i < l.size(); i++) {
        l[i] += r[i];
    }
    update(l);
}

void pluss(std::vector <long long> &l, std::vector <long long> &r, int k) {
    //std::cout << k << "\n";
    for (int i = 0; i < r.size(); i++) {
        l[i + k] += r[i];
    }
    update(l, 0);
}

void prnt(std::vector<long long> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}


std::vector<long long> mul(std::vector <long long> &a, std::vector <long long> &b) {
    std::vector<long long> ans(a.size() + b.size());

    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            ans[i + j] += a[i] * b[j];

    update(ans);
    return ans;
}

std::vector <long long> karatsuba(std::vector <long long> &a, std::vector <long long> &b, int ttt = 0) {
    if (a.size() <= 20 && b.size() <= 20) {
        return mul(a, b);
    }
    else {
        fill(a, b);
        int mid = (a.size() + 1) / 2;
        //std::cout << mid << "\n";
        std::vector<long long> l(mid);
        std::vector<long long> r(mid);

        std::vector<long long> a2(mid);
        std::vector<long long> a1(mid);

        std::vector<long long> b2(mid);
        std::vector<long long> b1(mid);

        for (int i = 0; i < mid; i++) {
            a1[i] = a[i];
            b1[i] = b[i];
            l[i] = a[i];
            r[i] = b[i];
            if (i + mid < a.size()) {
                a2[i] = a[mid + i];
                b2[i] = b[mid + i];
                r[i] += b[mid + i];
                l[i] += a[mid + i];
            }
        }

        update(l, 0);
        update(r, 0);
        /*if (ttt == 0) {
            std::cout << "l " << "\n";
            prnt(l);
            std::cout << "r " << "\n";
            prnt(r);
        }
         */

        std::vector<long long> t = karatsuba(l, r, ttt + 1);
        /*if (ttt == 0) {
            std::cout << "t " << "\n";
            prnt(t);
        }
        */

        std::vector<long long> p1 = karatsuba(a1, b1, ttt + 1);



        std::vector<long long> p2 = karatsuba(a2, b2, ttt + 1);


        std::vector<long long> ans(a.size() + b.size(), 0);

        for (int i = 0; i < p1.size(); i++) {
            ans[i] += p1[i];
            ans[i + mid] -= p1[i];

        }

        for (int i = 0; i < t.size(); i++) {
            ans[i + mid] += t[i];
        }

        for (int i = 0; i < p2.size(); i++) {
            ans[i + 2 * mid] += p2[i];
            ans[i + mid] -= p2[i];
        }


        update(ans);
        //std::cout << std::endl;
        return ans;
    }
}

void my_print(long long a) {
    if (10000 <= a && a <= 99999) {
        std::cout << a;
    }
    else if (1000 <= a && a <= 9999) {

        std::cout << a;
        std::cout << "";
    }
    else if (100 <= a && a <= 999) {
        std::cout << "0";
        std::cout << a;

    }
    else if (10 <= a && a <= 99) {
        std::cout << "00";
        std::cout << a;

    }
    else if (1 <= a && a <= 9) {
        std::cout << "000";
        std::cout << a;

    }
    else {
        std::cout << "0000";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::vector<long long> num1, num2;
    std::string a, b;

    //const std::clock_t c_start = std::clock();

    int k1 = 0;
    int k2 = 0;
    std::cin >> a >> b;
    //for (int i  = 0; i < 200000; i++) {
    //    a.push_back('9');
    //    b.push_back('9');
    //}
    int fl = 1;
    if (a[0] == '-') {
        fl *= -1;
        k1 = 1;
    }
    if (b[0] == '-'){
        k2 = 1;
        fl *= -1;
    }

    long long x = 0;
    long long tmp = 1;
    for (int i = a.size() - 1; i >= k1; i--) {
        x += (a[i] - '0') * tmp;
        tmp *= 10;
        if (tmp == BLOCK_SZ) {
            num1.push_back(x);
            x = 0;
            tmp = 1;
        }
    }

    if (num1.size() == 0 || x != 0) {
        num1.push_back(x);
    }

    x = 0;
    tmp = 1;
    for (int i = b.size() - 1; i >= k2; i--) {
        x += (b[i] - '0') * tmp;
        tmp *= 10;

        if (tmp == BLOCK_SZ) {
            num2.push_back(x);
            x = 0;
            tmp = 1;
        }
    }


    if (num2.size() == 0 || x != 0) {
        num2.push_back(x);
    }

    fill(num1, num2);
    //prnt(num1);
    //prnt(num2);

    std::vector<long long> ans = karatsuba(num1, num2);
    if (fl == -1) {
        std::cout << '-';
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
        if (i == ans.size() - 1) {
            std::cout << ans[i];
        }
        else {
            my_print(ans[i]);
        }

    }
    //const std::clock_t c_end = std::clock();
    //std::cout << std::endl;
    //std::cout << ((c_end - c_start) / double(CLOCKS_PER_SEC));

}