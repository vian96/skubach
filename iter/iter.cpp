#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <set>
#include <cctype>

using namespace std;

void first (const vector<int> &v, const int num) {
    auto it = std::make_reverse_iterator (
            std::find_if (v.begin(), v.end(), [num] (const int i) {
                return i > num;
            })
        );
    std::for_each (it, v.rend(), [] (const int &i) {
            std::cout << i << ' ';
        });
}

vector<string> split (string str) {
    vector<string> res;
    auto test_space = [](char c) { return std::isspace(c); };
    auto left = std::find_if_not (str.begin(), str.end(), test_space); // to remove first spaces
    auto right = std::find_if (left, str.end(), test_space);

    while (right != str.end()) {
        res.push_back (string(left, right));
        left = std::find_if_not (right, str.end(), test_space);
        right = std::find_if (left, str.end(), test_space);
    }

    if (left != right) // to remove last spaces
        res.push_back (string(left, right));
    return res;
}

template<typename T> 
vector<T> third (set<T> &s, const T &elem) {
    vector<T> res;
    auto it = std::make_reverse_iterator (
            std::find_if (s.begin(), s.end(), [elem] (const T &i) {
                return i > elem;
            })
        );
    
    std::copy(s.rbegin(), it, std::back_inserter (res));

    return res;
}

int main() {
    vector<int> v = {154,452,-123,89894,555,6,4546567,-558};
    first(v, 555);
    std::cout << endl;

    string str = " sd ss s  ababa nohoko   ";
    auto res2 = split (str);
    std::for_each (res2.begin(), res2.end(), [](const string &i) { std::cout << i << '|'; });
    std::cout << endl;

    set<double> s = {545, 45, 6, 445, -44, -12.316, -454.454, 45.4};
    auto res3 = third (s, 44.2);
    std::for_each (res3.begin(), res3.end(), [](const double &i) { std::cout << i << ' '; });
    std::cout << endl;

    // OUT:
    // -123 452 154
    // sd|ss|s|ababa|nohoko|
    // 545 445 45.4 45
}
