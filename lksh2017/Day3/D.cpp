#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<int, int>>  V;
    vector<pair<int, int>> ans;

    int m, l, r;
    cin >> m;
    for (;;) {
        cin >> l >> r;
        if (l == 0 && r == 0)
            break;
        else
            V.emplace_back(l, r);
    }
    V.emplace_back(1e9, 1e9);

    sort(V.begin(), V.end());

    pair<int, int> max_r = {0, 0};
    int bound = 0;
    for (size_t i = 0; i < V.size(); ++i) {
        if (bound >= m)
            break;
        max_r = max(max_r, {V[i].second, V[i].first});
        auto k = max_r;
        if (V[i + 1].first > bound && k.second <= bound) {
            ans.emplace_back(k.second, k.first);
            bound = k.first;
        }
    }

    if (bound < m || ans[0].first > 0) {
        cout << "No solution";
        return 0;
    }

    cout << ans.size() << "\n";
    for (auto i : ans)
        cout << i.first << " " << i.second << "\n";
}
