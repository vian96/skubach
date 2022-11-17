#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void my_sort(vector<int> &v) {
    int was_swap = 1;
    while (was_swap) {
        was_swap = 0;
        for (int i = 0; i < v.size() - 1; i++)
            if (v[i] > v[i+1]) {
                swap(v[i], v[i+1]);
                was_swap = 1;
            }
    }
}

int main() {
    int n = 0; 
    vector<int> v;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x = 0;
        cin >> x;
        v.push_back(x);
    }
    my_sort(v);
    for (int i = 0; i < n; i++) 
        cout << v[i] << ' ';
    cout << endl;
}
