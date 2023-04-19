#include "../animal/animal.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include <utility>
#include <cstdlib>

using namespace std::chrono;

template<typename T, typename... Args>
int function_time(T func, int reps, Args &... args) {
    auto start = high_resolution_clock::now();

    for (int i = 1; i <= reps; i++) 
        func(i, args...);
    
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

//  помимо вектора еще для дека и листа

template<typename T>
void test_pb(int i, T &cont) {
    cont.push_back(i);
}

template<typename T>
void test_pf(int i, T &cont) {
    cont.push_front(i);
}

template<typename T>
void test_insert_front(int i, T &cont) {
    cont.insert(cont.begin(), i);
}

template<typename T>
void test_access(int i, T &cont) {
    cont[i] = cont[i]*2 + 3;
}

template<typename T>
void test_it_inc(int i, T &cont) {
    auto it = cont.begin();
    for (int k = 0; k < i; k++)
            it++;
}

template<typename T>
void test_for(int i, T &cont) {
    for (auto &it : cont)
        it = it*3 + 2;
}

template<typename T>
void test_insert_mid(int i, T &cont) {
    cont.insert(cont.begin() + cont.size()/2, i);
}

template<typename T>
void test_insert_iter(int i, T &cont, typename T::iterator it) {
    cont.insert(it, i);
}

template<typename T, typename... Args>
void run_fors(T func, int reps, std::fstream &f_out, Args &... args) {
    for (int i = 4; i <= reps; i = i + i/4)
        f_out << function_time(func, i, args...) << ' ';
}

template<typename T>
void test_erase_iter(int i, T &cont, typename T::iterator &it) {
    it = cont.erase(it);
}

template<typename T>
void test_erase_mid(int i, T &cont) {
    cont.erase(cont.begin() + cont.size()/2);
}

int main() {
    std::vector<int> v(30e5);
    std::list<int> l(30e5);
    std::deque<int> d(30e5);
    
    // PUSH BACK
    while (0)
    {
        std::fstream f_pb("pb.txt", std::ios::out);
        f_pb << "vector ";
        run_fors(test_pb<std::vector<int> >, 10e4, f_pb, v);
        f_pb << "\nlist ";
        run_fors(test_pb<std::list<int> >, 10e4, f_pb, l);
        f_pb << "\ndeque ";
        run_fors(test_pb<std::deque<int> >, 10e4, f_pb, d);
        f_pb.close();
        std::system("graph.py pb.txt");
    }

    // PUSH FRONT
    while (0)
    {
        std::fstream f_pf("pf.txt", std::ios::out);
        // commented bc too long, another graph created
        // f_pf << "vector ";
        // run_fors(test_insert_front<std::vector<int> >, 10e4, f_pf, v);
        f_pf << "list ";
        run_fors(test_pf<std::list<int> >, 10e4, f_pf, l);
        f_pf << "\ndeque ";
        run_fors(test_pf<std::deque<int> >, 10e4, f_pf, d);
        f_pf.close();
        std::system("graph.py pf.txt");
    }

    // ELEMENT ACCESS
    while (0)
    {
        std::fstream f_el("el.txt", std::ios::out);
        f_el << "vector ";
        run_fors(test_access<std::vector<int> >, 10e4, f_el, v);
        // list is very long, calculated once
        // f_el << "\nlist ";
        // run_fors(test_it_inc<std::list<int> >, 10e4, f_el, l);
        f_el << "\ndeque ";
        run_fors(test_access<std::deque<int> >, 10e4, f_el, d);
        f_el.close();
        std::system("graph.py el.txt");
    }

    // FOR
    // TOO LOONG :(
    while (0)
    {
        std::fstream f_for("for.txt", std::ios::out);
        f_for << "vector ";
        run_fors(test_for<std::vector<int> >, 10e4, f_for, v);
        f_for << "\nlist ";
        run_fors(test_for<std::list<int> >, 10e4, f_for, l);
        f_for << "\ndeque ";
        run_fors(test_for<std::deque<int> >, 10e4, f_for, d);
        f_for.close();
        std::system("graph.py for.txt");
    }

    // INSERT IN MIDDLE
    while (0)
    {
        std::fstream f_mid("mid.txt", std::ios::out);
        f_mid << "vector ";
        run_fors(test_insert_mid<std::vector<int> >, 10e4, f_mid, v);
        auto it = l.begin();
        for (int i = 0; i < l.size()/2; i++)
            it++;
        f_mid << "\nlist ";
        run_fors(test_insert_iter<std::list<int> >, 10e4, f_mid, l, it);
        f_mid << "\ndeque ";
        run_fors(test_insert_mid<std::deque<int> >, 10e4, f_mid, d);
        f_mid.close();
        std::system("graph.py mid.txt");
    }

    // ERASE IN MIDDLE
    {
        std::fstream f_ermid("ermid.txt", std::ios::out);
        f_ermid << "vector ";
        run_fors(test_erase_mid<std::vector<int> >, 10e3, f_ermid, v);
        std::cout << "finished vector\n";
        auto it = l.begin();
        for (int i = 0; i < l.size()/2; i++)
            it++;
        f_ermid << "\nlist ";
        run_fors(test_erase_iter<std::list<int> >, 10e3, f_ermid, l, it);
        std::cout << "finished list\n";
        f_ermid << "\ndeque ";
        run_fors(test_erase_mid<std::deque<int> >, 10e3, f_ermid, d);
        f_ermid.close();
        std::system("graph.py ermid.txt");
    }

    // std::cout << "push_back\n";
    // std::cout << function_time(test_pb<std::vector<int> >, 10e4, v) << '\n';
    // std::cout << function_time(test_pb<std::list<int> >, 10e4, l) << '\n';
    // std::cout << function_time(test_pb<std::deque<int> >, 10e4, d) << '\n';

    // std::cout << "\nelement access with no list :(\n";
    // std::cout << function_time(test_access<std::vector<int> >, 10e4, v) << '\n';
    // std::cout << function_time(test_access<std::deque<int> >, 10e4, d) << '\n';

    // std::cout << "\nfor\n";
    // std::cout << function_time(test_for<std::vector<int> >, 100, v) << '\n';
    // std::cout << function_time(test_for<std::list<int> >, 100, l) << '\n';
    // std::cout << function_time(test_for<std::deque<int> >, 100, d) << '\n';

    // std::cout << "\ninsert in middle\n";
    // std::cout << function_time(test_insert_mid<std::vector<int> >, 10e4, v) << '\n';
    // auto it = l.begin();
    // for (int i = 0; i < l.size()/2; i++)
    //     it++;
    // std::cout << function_time(test_insert_iter<std::list<int> >, 10e4, l, it) << '\n';
    // std::cout << function_time(test_insert_mid<std::deque<int> >, 10e4, d) << '\n';
}

