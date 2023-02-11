#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

using namespace std;

class Worker {
public:
    string name;
    int salary;
    int age;
    ofstream &f_out;

    Worker(string name_, int salary_, int age_, ofstream &f_out_) : 
        name(name_), salary(salary_), age(age_), f_out(f_out_) {
            f_out << setfill('.');
    };

    void dowork() {
        f_out << left << setw(10) << name  << setw(10) << age << setw(10) << salary << endl;

        salary--;
        if (salary == 100)
            throw underflow_error("МАЛО ДЕНЕГ");
    }
};

typedef struct MyData {
    Worker *wrkr;
    int val2;
} MYDATA, *PMYDATA;

DWORD WINAPI MyThreadFunction( LPVOID lpParam );
void ErrorHandler(LPCTSTR lpszFunction);

int main() {
    ifstream f_in("workers.txt");
    int salary = 0;
    f_in >> salary;

    ofstream f_out("output.txt");
    int n = 10;
    vector<Worker> v;
    for (int i = 0; i < n; i++) {
        v.push_back(Worker(string("wrkr").append(to_string(i)), salary, i+20, f_out));
    }

    const int MAX_THREADS = 10;
    
    MYDATA DataArray[MAX_THREADS];
    DWORD dwThreadIdArray[MAX_THREADS];
    HANDLE hThreadArray[MAX_THREADS]; 

    for (int i = 0; i < MAX_THREADS; i++) {
        DataArray[i].wrkr = &v[i];
        hThreadArray[i] = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            DataArray + i,          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[i]     // returns the thread identifier 
        );
    }

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    for(int i = 0; i < MAX_THREADS; i++)
        CloseHandle(hThreadArray[i]);
}

DWORD WINAPI MyThreadFunction (LPVOID lpParam) { 
    PMYDATA pdat = (PMYDATA) lpParam;
    Worker *pwrkr = pdat->wrkr;

    while (pwrkr->salary > 100) {
        try {
            pwrkr->dowork();
        }
        catch (underflow_error &ex) {
            cout << pwrkr->name << " is hired!\n";
        }
    }

    return 0; 
} 


