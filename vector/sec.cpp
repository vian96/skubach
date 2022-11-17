#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void reverse(vector<int> &v) {
    for (int i = 0; i < v.size()/2; i++) 
        swap(v[i], v[v.size() - 1 - i]);
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
    reverse(v);
    for (int i = 0; i < n; i++) 
        cout << v[i] << ' ';
    cout << endl;
}
