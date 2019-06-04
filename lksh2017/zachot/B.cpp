#include <bits/stdc++.h>


using namespace std;

int main() {
    vector<pair<int, int>> ev;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int i = 0; i < k; ++i) {
            int h, m, s, q;
            scanf("%d : %d : %d", &h, &m, &s);
            s += m * 60 + h * 60 * 60;
            cin >> q;
            ev.emplace_back(s, q);
        }
    }
    sort(ev.begin(), ev.end());
    int bal = 0, min_bal = 1e9;
    for (auto i : ev) {
        bal += i.second;
        min_bal = min(bal, min_bal);
    }
    if (ev.size() == 0 || min_bal > 0)
        min_bal = 0;
    cout << -min_bal;
}