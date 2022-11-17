#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() { 
    vector<string> words(3);
    cin >> words[0] >> words[1] >> words[2];
    int cnt = count(words[0].begin(), words[0].end(), 'o');
    sort(words.begin(), words.end());
    cout << words[0] << ' ' << words[1] << ' ' << words[2] << endl << cnt;
    cout << endl;
}
