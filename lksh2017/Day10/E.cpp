#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int INF = 1e9;

int main() {
    string x;
    int k, m;
    cin >> x >> k >> m;
    vector<int> d(m);
    for (int i = 0; i < m; ++i) {
        cin >> d[i];
    }
    sort(d.begin(), d.end());

    int res = 0;
    for (auto &i : x) {
        int p = i - '0';
        res *= 10;
        res += p;
        res %= k;
    }

    vector<int> pr(k);
    vector<int> chan(k);
    vector<int> dist(k, INF);


    pr[res] = -1;
    dist[res] = 0;

    queue<int> q;
    q.push(res);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (auto &i : d) {
            int n = (curr * 10 + i) % k;
            if (dist[n] > dist[curr] + 1) {
                dist[n] = dist[curr] + 1;
                q.push(n);
                pr[n] = curr;
                chan[n] = i;
            }
        }
    }
    if (dist[0] == INF) {
        cout << -1;
        return 0;
    }

    vector<int> suf;
    int curr = 0;
    while (curr != res) {
        suf.push_back(chan[curr]);
        curr = pr[curr];
    }
    reverse(suf.begin(), suf.end());
    cout << x;
    for (auto &i : suf) {
        cout << i;
    }
}