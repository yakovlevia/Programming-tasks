#include <iostream>
#include <vector>
using namespace std;

// 752

class SegTree{
public:
    pair<int, int> neutral = {-1e9, -1}; // значение элемента такого, чтобы fun(x, neutral) = x
                     // Например, для суммы это 0, для произведения 1, для максимума -INF, для минимума +INF
    int size = 0;    // размер массива, на котором строится дерево отрезков
    vector <pair<int, int>> tree; // массив в котором хранится дерево отрезков
    vector <int> toupd; // вспомогательный массив для осуществления отложенного обновления на отрезке

    pair<int, int> comb(pair <int, int> a, pair <int, int> b){ // пример специальной функции на которой строится дерево отрезков
        if (a.first == b.first) return {a.first, min(a.second, b.second)};// в данном примере эта функция возвращает пару {максимум из всех чисел, количесво раз которое он встречается}
        else if (a.first > b.first) return a;
        else return b;
    }

    void init(int n){ //инициализирование самого дерева и вспомогательного массива для обновления на отрезке
        tree.clear();
        tree.resize(4 * n, {0, 0});
        toupd.clear();
        toupd.resize(4 * n, 0);
        size = n;
    }



    void build(vector <int> &a, int v, int l, int r){ // построение дерева отрезков по заданному массиву
        if (l == r){
            tree[v] = {a[l], l};
        }
        else {
            int m = (l + r) / 2;//середина
            build(a, v * 2 + 1, l, m);//построение левой части
            build(a, v * 2 + 2, m + 1, r);//построение правой части
            tree[v] = comb(tree[v * 2 + 1], tree[v * 2 + 2]); // если у вас особая функция, то тут должно быть tree[v] = comb(tree[v * 2 + 1], tree[v * 2 + 2])
        }
    }

    void build(vector <int> &a){ // перегрузка построения для удобства
        build(a, 0, 0, size - 1);
    }





    pair<int, int> get(int v, int tl, int tr, int pos){ // получение значения элемента в конкретной позиции
        if (tl == tr){
            return tree[v];
        }
        else {
            int mid = (tl + tr) / 2;
            if (pos <= mid){
                return get(v * 2 + 1, tl, mid, pos);
            }
            else {
                return get(v * 2 + 2, mid + 1, tr, pos);
            }
        }
    }

    pair <int, int> get(int v, int tl, int tr, int l, int r){ // получение значения(в данном примере суммы) на каком-либо подотрезке
        if (l > r) return neutral;
        else if (tl == l && tr == r){
            return tree[v];
        }
        else {
            int mid = (tl + tr) / 2;
            return comb(get(v * 2 + 1, tl, mid, l, min(r, mid)), get(v * 2 + 2, mid + 1, tr, max(mid + 1, l), r));
        }
    }

    pair<int, int> get(int pos){ // перегрузка для удобного вызова функции get в конкретной позиции
        return get(0, 0, size - 1, pos);
    }

    pair<int, int> get(int l, int r){ // перегрузка для удобного вызова функции get на отрезке
        return get(0, 0, size - 1, l, r);
    }

};

int main() {
    int n;
    cin >> n;
    vector <int> arr(n);
    for (auto &q : arr){
        cin >> q;
    }
    SegTree my_tree;
    my_tree.init(n);
    my_tree.build(arr);
    int q;
    cin >> q;//ввод количества запросов
    while(q--){
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        pair<int, int> ans = my_tree.get(l, r);
        cout << ans.first << " " << ans.second + 1 << '\n';
    }
}