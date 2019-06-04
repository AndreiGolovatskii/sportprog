#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, s, f;
    cin >> n >> m >> s >> f;
    vector<vector<pair<int, double>>> g(n + 1);
    for (int i = 0; i  < m; ++i) {
        int v, u;
        double w;
        cin >> v >> u >> w;
        w = (100 - w) / 100;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }
    vector<double> d(n + 1, 0);
    d[s] = 1;

    vector<bool> used(n + 1, false);

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 1; j <= n; ++j) {
            if (!used[j] && (v == -1 || d[j] > d[v])) {
                v = j;
            }
        }
        if (v == -1) {
            break;
        }

        used[v] = true;
        for (size_t j = 0; j < g[v].size(); ++j) {
            int to = g[v][j].first;
            double w = g[v][j].second;

            if (d[v] * w > d[to]) {
                d[to] = d[v] * w;
            }
        }
    }
    cout << 1 - d[f];
}
