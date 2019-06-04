#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;

const int H = 60 * 60;
const int M = 60;
const int D = 24 * 60 * 60;

int main() {
    int n;
    vector<pair<int, int>> events;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int h, m, s;
        int he, me, se;
        cin >> h >> m >> s;
        cin >> he >> me >> se;
        s += m * M + h * H;
        se += me * M + he * H;
        if (se == 0) {
            se = D;
        }
        if (s == se) {
            s = 0;
            se = D;
        }
        if (s > se) {
            events.emplace_back(D, -1);
            events.emplace_back(0, 1);
        }
        events.emplace_back(s, 1);
        events.emplace_back(se, -1);
    }

    sort(events.begin(), events.end());

    int count = 0;
    int ans = 0;
    for (size_t i = 0; i < events.size() - 1; ++i) {
        count += events[i].second;
        if (count == n){
            ans += events[i + 1].first - events[i].first;
        }
    }

    cout << ans;
}
