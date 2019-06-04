#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

int main() {
    ifstream cin("union.in");
    ofstream cout("union.out");

    int n;
    cin >> n;

    vector<tuple<int, int, int, int>> Ox;
    vector<int> Oy;
    map<int, int> count;
    for (int i = 0; i < n; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2 || y1 == y2)
            continue;
        Ox.emplace_back(x1, -1,  y1, y2);
        Ox.emplace_back(x2, 1,  y1, y2);
        //count[y1] = 0;
        //count[y2] = 0;
        //Oy.push_back(y1);
        //Oy.push_back(y2);
    }

    sort(Ox.begin(), Ox.end());
    //sort(Oy.begin(), Oy.end());
    //Oy.resize(unique(Oy.begin(), Oy.end()) - Oy.begin());

    int start = 0;
    long long ans = 0;
    for (auto event : Ox) {
        int bal = 0, a = 0;
        int y;
        for (auto i : count) {
            if (bal > 0)
                a += i.first - y;
            bal += i.second;
            y = i.first;
        }

        ans +=(long long)a * (get<0>(event) - start);
        start = get<0>(event);

        count[get<2>(event)] -= get<1>(event);
        count[get<3>(event)] += get<1>(event);
    }
    cout << ans;
}
