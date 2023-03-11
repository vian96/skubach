#include "list.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1,6,5,97,-54,98};
    List<int> lis2{v}; // init from vector
    List<int> lis{lis2}; // init from list
    std::cout << "\n||\n" << lis << lis2; // cout and for(i:list) test

    // push/pop tests
    lis.push_back(37);
    lis.push_front(-37);
    lis.push_front(-42);
    lis.push_back(42);

    lis.pop_back();
    lis.push_back(66);
    lis.pop_front();
    lis.push_front(-66);

    std::cout << "\n||\n" << lis << lis2;

    // pop and =/init test
    lis.pop_back();
    lis.pop_back();
    lis.pop_back();
    lis.pop_back();
    
    // insert test (probably not safe to use inserts in the same line)
    std::cout << *lis.insert(lis.begin(), 4456) << '\n' << 
                *lis.insert(lis.end(), 798997) << '\n' << *lis.insert(lis.begin()+3, 11111);
    std::cout << "\n||\n" << lis << lis2;

    // erase test
    lis2.erase(lis2.begin());
    lis2.erase(lis2.end()-1);
    lis2.erase(lis2.begin()+1);
    std::cout << "\n||\n" << lis << lis2;

    // Boundary checks
    // *lis.end();
    // lis.end()++;
    // lis.begin()--;
    // lis.begin() + 100500;
    // lis.end() - 100500;
    // lis[999];
    lis[-999];

    std::cout << '\n';
}

// OUTPUT 
// ||
// 1 6 5 97 -54 98
// 1 6 5 97 -54 98

// ||
// -66 -37 1 6 5 97 -54 98 37 66
// 1 6 5 97 -54 98
// 4456
// 798997
// 11111
// ||
// 4456 -66 -37 11111 1 6 5 97 798997
// 1 6 5 97 -54 98

// ||
// 4456 -66 -37 11111 1 6 5 97 798997
// 6 97 -54




