#include <map>
#include <vector>
#include <iostream>
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


int main() {
    std::pair<int, int> pr{100, -45};
    std::cout << pr;

    std::vector<int> v;
    for (int i=0; i < 10; i++)
        v.push_back(i);

    std::cout << v << "\n\n";

    std::map<int, int> mp;
    for (int i=0; i < 10; i++)
        mp[i] = 100-i;

    std::cout << mp << "\n\n";

    // if you want another separator so much, you can do this
    operator<< <std::map<int, int>, '|'> (std::cout, mp);
}
