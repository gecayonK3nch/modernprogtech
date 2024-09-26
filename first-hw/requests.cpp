#include <iostream>
#include <vector>
#include <list>
#include <random>

using namespace std;

void request_sort(vector<int>& a, int k) {
    vector<int> C(k, 0);
    for (int x: a) ++C[x];
    for (int i = 1; i < C.size(); ++i) {
        C[i] += C[i - 1];
    }
    a = C;
}


int main()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> based(n);
    mt19937 mt;
    uniform_int_distribution<int> d{0, k - 1}; //установка нижней и верхней границы генерации псевдослучайных чисел
    for (int i = 0; i < n; ++i) {
        based[i] = d(mt); //заполнение массива псевдослучайными числами в соответствии с условием
    }
    for (int i = 0; i < n; ++i) {
        cout << based[i] << " ";
    }
    cout << endl;
    request_sort(based, k);
    for (int i = 0; i < k; ++i) {
        cout << based[i] << " ";
    }
    cout << endl;
    for (int i; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << based[r] - based[l - 1] << endl;
    }
    
    return 0;
}
