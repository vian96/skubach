#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print_str_vec_except (const vector<string> &v, const string &str) {
    for (auto &i:v)
        if (i != str)
            cout << i << ' ';
    cout << endl;
}

int main() {
    int q = 0;
    cin >> q;
    map<string, vector<string> > buses;
    map<string, vector<string> > stops_map;
    
    for (int i = 0; i < q; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "NEW_BUS") {
            string name;
            cin >> name;

            int stops_cnt = 0;
            cin >> stops_cnt;
            vector<string> stops (stops_cnt);
            for (int i = 0; i < stops_cnt; i++) {
                cin >> stops[i];
                stops_map[stops[i]].push_back (name);
            }

            buses[name] = stops;
        }

        if (cmd == "BUSES_FOR_STOP") {
            string stop;
            cin >> stop;
            if (stops_map.count (stop) == 0)
                cout << "No stop\n";
            else
                print_str_vec_except (stops_map[stop], "");
        }

        if (cmd == "STOPS_FOR_BUS") {
            string name;
            cin >> name;
            if (buses.count (name) == 0) {
                cout << "No bus\n";
                continue;
            }
            for (auto &stop : buses[name]) {
                cout << "Stop " << stop << ": ";
                if (stops_map[stop].size() == 1)
                    cout << "no interchange\n";
                else
                    print_str_vec_except (stops_map[stop], name);
            }
        }

        if (cmd == "ALL_BUSES") {
            if (buses.size() == 0) {
                cout << "No buses\n";
                continue;
            }

            for (const auto& [key, value] : buses) {
                cout << "Bus " << key << ": ";
                print_str_vec_except (value, "");
            }
        }
    }
}