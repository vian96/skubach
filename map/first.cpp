#include <iostream>
#include <map>
#include <string>

using namespace std;

map<char, int> get_map (string str) {
    map<char, int> ans;
    for (int i = 0; i < str.size(); i++) {
        ans[str[i]]++;
    }
    return ans;
}

int main() {
    int n = 0;
    cin >> n;
    string word1, word2;
    for (int i = 0; i < n; i++) {
        cin >> word1 >> word2;
        if (get_map (word1) == get_map (word2))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
