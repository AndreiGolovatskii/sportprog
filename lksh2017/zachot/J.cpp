#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

const int INF=1e9;

bool is_neb(int s1, int s2, vector<vector<int>> &g) {
    for (auto i : g[s1]) {
        if (i == s2)
            return true;
    }
    return false;
}

int main()
{
    cout.precision(10);
    cout << fixed;
    int n, m, s1, s2, f1, f2;
    cin >> n >> m >> s1 >> s2 >> f1 >> f2;
    vector<vector<int>> g(n+1);
    for (int i = 1; i < n + 1; ++i) {
        g[i].push_back(i);
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    queue<vector<int>> q;
    vector<vector<vector<int>>> pr(n+1, vector<vector<int>>(n + 1));
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, 1e9));
    dist[s1][s2] = 0;
    q.push({s1, s2});
    while (!q.empty()) {
        int s1 = q.front()[0];
        int s2 = q.front()[1];
        q.pop();
        for (int e = 0; e < g[s1].size(); ++e) {
            for (int p = 0; p < g[s2].size(); ++p) {
                int to1 = g[s1][e];
                int to2 = g[s2][p];
                if (to1 == s1 && to2 == s2)
                    continue;
                int k = 0;
                if (to1 != s1)
                    k++;
                if (to2 != s2)
                    k++;
                if (dist[to1][to2] > dist[s1][s2] + k && to1 != to2 &&
                        (to2 != s1 || to1 != s2) && is_neb(to1, to2, g)) {
                    dist[to1][to2] = dist[s1][s2] + k;
                    q.push({to1, to2});
                    pr[to1][to2] = {s1, s2};
                }
            }
        }
    }
    cout << dist[f1][f2] << " ";
    vector<vector<int>> ans;
    ans.push_back({f1, f2});
    while (f1 != s1 || f2 != s2) {
        auto p = pr[f1][f2];
        f1 = p[0];
        f2 = p[1];
        ans.push_back({f1, f2});
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i[0] << " " << i[1] << endl;
    }
    system("pause");
}

