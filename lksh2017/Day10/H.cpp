#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;


int main() {
    int n, m, k, s, f;
    cin >> n >> m >> k >> s >> f;
    vector<vector<int>> g;
    for (int i = 0; i < m; ++i) {
        int s, f, p;
        cin >> s >> f >> p;
        g.push_back({s, f, p});
    }
    vector<vector<int>> dist(k + 1, vector<int>(n + 1, INF));
    dist[0][s] = 0;
    for (int p = 0; p < k; ++p) {
        for (auto &i : g) {
            int v = i[0];
            int u = i[1];
            int w = i[2];
            dist[p + 1][u] = min(dist[p + 1][u], dist[p][v] + w);
        }
    }
    int ans = INF;
    for (int p = 0; p <= k; ++p) {
        ans = min(ans, dist[p][f]);
    }
    if (ans == INF) {
        cout << -1;
        return 0;
    }

    cout << ans;
}
