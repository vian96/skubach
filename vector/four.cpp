#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n = 0, a = 0; 
    vector<int> v;
    cin >> a >> n;
    for (int i = 0; i < n; i++) {
        int x = 0;
        cin >> x;
        v.push_back(x);
    }
    int min_val = 1 << 30, min_ind = -1;
    for (int i = 0; i < n; i++) 
        if (v[i] > a && v[i] < min_val) {
            min_ind = i;
            min_val = v[i];
        }
    cout << min_ind;
    cout << endl;
}
