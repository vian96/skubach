#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <concepts>
#include <vector>
#include <utility>
#include <concepts>

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pr) {
    return os << pr.first << ' ' << pr.second;
}

template<typename Container>
concept Iterable = requires(Container t) {
        { *t.begin()++, t.end() }; // it has end and you can increment and dereference begin
};

template<Iterable T, const char sep = '\n'>
    // it does not have overload yet
    requires (!requires(std::ostream o, T a) { operator<<(o, a); }) 
std::ostream& operator<<(std::ostream& os, const T& cont) {
    for(const auto& it : cont)
        os << it << sep;
    return os;
}

// checks if elem is in v
template<typename T>
bool f1 (const std::vector<T> &v, const T &elem) {
    return std::find (v.begin(), v.end(), elem) != v.end();
} 

// checks if elem is in mp
template<typename T, typename U>
bool f1(const std::map<T, U> &mp, const T &elem) {
    return std::find_if(
                mp.begin(), mp.end(), 
                [elem] (auto &i) { return i.second == elem; }
            ) != mp.end();
} 

// checks if even size
template<typename T, typename U>
    // requires (T t) { t.size() % 2 == 0};
bool f2 (const T &cont, const U &elem) {
    return cont.size() % 2 == 0;
}

class Checker {
public:
    int counter = 0 ; /* counts how much true */

    template<typename fT, typename Container, typename T>
    void check (fT foo, std::vector<Container> v, T elem) { 
        counter += std::count_if (
                    v.begin(), v.end(), 
                    [elem, foo] (Container i) { return foo(i, elem); }
            );
    }
    
    ~Checker () {
        std::cout << counter << std::endl;
    }
};

int main () {
    std::vector<std::vector<int> > vv(15);
    for (int i = 0; i < vv.size(); i++)
        std::generate_n(
            std::inserter(vv[i], vv[i].begin()), i, 
            [i] () { 
                static int cnt = -1; 
                cnt++; 
                return cnt - (i*(i-1)/2); 
            }
        );

    std::vector<std::map<int, int> > vm(15);
    for (int i = 0; i < vm.size(); i++)
        std::generate_n(
            std::inserter(vm[i], vm[i].begin()), i, 
            [i] () { 
                static int cnt = -1; 
                cnt++; 
                int cur = cnt - (i*(i-1)/2); 
                return std::make_pair(cur, 100 - cur);
            } 
        );
    
    Checker chc;
    chc.check (f1<int>, vv, 7); // 7 elems in vv contain 7
    chc.check (f1<int, int>, vm, 7); // 0 elems in vm contain 7
    chc.check (f1<int, int>, vm, 97); // 11 elems in vm contain 97

    chc.check (f2<std::vector<int>, int>, vv, -1); // 8 elems in vv have even size
    chc.check (f2<std::map<int, int>, int>, vm, -1); // 8 elems in vm have even size

    std::cout << std::endl; // after that chc should cout 34
    // std::for_each (vm.begin(), vm.end(), [](std::map<int, int> v) { std::cout << f1(v, 97) << v << "\n\n"; });
    return 0 ;
}
