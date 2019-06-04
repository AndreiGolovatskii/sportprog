#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;


int main() {
    ofstream cout("transfers.out");
    ifstream cin("transfers.in");
    vector<pair<int, int> > Bus(4);
    int a1, a2, b1, b2;
    cin >> a1 >> a2 >> b1 >> b2;
    Bus[0] = {max(a1, a2), 2};
    Bus[1] = {min(a1, a2), 1};
    Bus[2] = {max(b1, b2), 2};
    Bus[3] = {min(b1, b2), 1};

    sort(Bus.begin(), Bus.end());
    bool f = false;
    int start = 0;
    int finish = 0;
    for (auto i : Bus) {
        if (f && i.second == 1)
            start = i.first;
        if (i.second == 1)
            f = true;
        if (i.second == 2) {
            if (start != 0)
                finish = i.first + 1;
            break;
        }
    }
    cout << finish - start;
}
