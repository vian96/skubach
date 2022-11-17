#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n = 0; 
    vector<double> marks;
    double sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double x = 0;
        cin >> x;
        sum += x;
        marks.push_back(x);
    }
    sum /= n;
    for (int i = 0; i < n; i++) {
        if (marks[i] > sum)
            cout << i << ' ';
    }
    cout << endl;
}
