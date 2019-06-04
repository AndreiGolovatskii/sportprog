#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <stack>


using namespace std;

struct event{
    int id, s, f;
    const bool operator<(event b){
        return s < b.s;
    }
};


int main() {
    int n;
    cin >> n;
    vector<event> ev(n);
    for (int i = 0; i < n; ++i) {
        ev[i].id = i + 1;
        cin >> ev[i].s >> ev[i].f;
    }
    sort(ev.begin(), ev.end());
    vector<int> ans;
    int finishtime = 0;
    for (int i = 0; i < n; ++i) {
        if (ev[i].s >= finishtime) {
            ans.push_back(ev[i].id);
            finishtime = ev[i].f;
        } else if (finishtime >= ev[i].f){
            finishtime = ev[i].f;
            ans.erase(--ans.end());
            ans.push_back(ev[i].id);
        }
    }
    for (auto i : ans) {
        cout << i << " ";
    }
}
