#include <iostream>
#include <vector>

using namespace std;

int int_pairs(vector<int> arr) {
    int cnt = 0;
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) {
                ++cnt;
            }
        }
    }
    return cnt;
}

vector<int> counting_merge(vector<int> arr_one, vector<int> arr_two, int* cnt) {
    vector<int> res;
    int i = 0, j = 0;
    int counter = 0;

    while (i < arr_one.size() && j < arr_two.size()) {
        if (arr_one[i] <= arr_two[j]) {
            res.push_back(arr_one[i]);
            ++i;
        } else {
            res.push_back(arr_two[j]);
            counter += (arr_one.size() - i);
            ++j;
        }
    }

    while (i < arr_one.size()) {
        res.push_back(arr_one[i]);
        ++i;
    }
    
    while (j < arr_two.size()) {
        res.push_back(arr_two[j]);
        ++j;
    }
    (*cnt) += counter;

    return res;
}

vector<int> counting_sort(vector<int> arr, int* cnt) {
    if (arr.size() <= 1) return arr;

    int mid = arr.size() / 2;
    vector<int> arr_one = counting_sort(vector<int>(arr.begin(), arr.begin() + mid), cnt);
    vector<int> arr_two = counting_sort(vector<int>(arr.begin() + mid, arr.end()), cnt);
    return counting_merge(arr_one, arr_two, cnt);
}

int main()
{
    vector<int> arr = {9, 1, 4, 7, 2, 8, 5, 6, 3, 0};

    int cnt = 0;
    int example = int_pairs(arr);
    arr = counting_sort(arr, &cnt);
    cout << endl << cnt << " " << example;

    return 0;
}
