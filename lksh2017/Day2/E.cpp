#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = (const long long int) 1e13;

vector<pair<int, long long>> tr;

long double pos(double time) {
    if (time < 0)
        return -INF;
    auto it = lower_bound(tr.begin(), tr.end(), make_pair((int)time, INF));
    it--;
    auto it1 = it + 1;

    long double delta_s = ((*it1).second - (*it).second);
    double delta_t = ((*it1).first - (*it).first);
    double t = (time - (*it).first);
    if (delta_t == 0)
        return (*it).second;
    else
        return (*it).second + delta_s * (t / delta_t);
}

bool dist(double delta_t, int min_dist) {
    vector<int> ev;
    for (auto &i : tr) {
        ev.push_back(i.first);
    }
    sort(ev.begin(), ev.end());
    for (auto &i : ev) {
        long double pos2 = pos(i - delta_t);
        long double pos1 = pos(i);
        if ( pos1 - pos2 < min_dist)
            return false;
    }
    return true;
}


int main() {
    int l, n;
    long  long tl = 0, ts = 0;
    cin >> l >> n;
    tr.emplace_back(0, 0);
    for (int i = 0; i < n; ++i) {
        int ti, vi;
        cin >> ti >> vi;
        tr.push_back({tl + ti, ts + ti * vi});
        tl += ti;
        ts += vi * ti;
    }

    double right = tr.rbegin() -> first;
    double left = 0;
    for (int i = 0; i < 100; ++i) {
        double mid = (left + right) / 2;
        if (dist(mid, l)) {
            right = mid;
        } else
            left = mid;
    }
    cout << right;
}
