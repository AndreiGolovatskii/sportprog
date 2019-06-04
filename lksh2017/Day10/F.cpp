#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

void call_inf() {
    cout << "infinitely kind";
    exit(0);
}

vector<int> recov(int i, int j, vector<vector<int>> &pr, int cnt, int n) {
    vector<int> ans;
    int k = pr[i][j];
    if (cnt > n) {
        call_inf();
    }
    if (k == -1) {
        ans.push_back(j);
        return ans;
    }
    auto ans1 = recov(i, k, pr, ++cnt, n);
    auto ans2 = recov(k, j, pr, ++cnt, n);
    for (auto &i : ans1) {
        ans.push_back(i);
    }
    for (auto &i : ans2) {
        ans.push_back(i);
    }
    return ans;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }
    vector<vector<int>> flights(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= m; ++i) {
        int b, e, w;
        cin >> b >> e >> w;
        w = -w;
        dist[b][e] = min(w, dist[b][e]);
        flights[b][e] = i;
    }

    vector<int> tr(k);
    for (int i = 0; i < k; ++i) {
        cin >> tr[i];
    }
    vector<vector<int>> pr(n + 1, vector<int>(n + 1, -1));
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF
                    && dist[i][j] > dist[i][k] + dist[k][j]) {
                    if (dist[i][k] + dist[k][j] < -INF)
                        dist[i][j] = -INF;
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pr[i][j] = k;
                }
            }
        }
    }
    vector<int> ans;
    int s = tr[0];
    for (int i = 1; i < k; ++i) {
        auto p = recov(tr[i - 1], tr[i], pr, 0, n);
        for (auto i : p) {
            ans.push_back(flights[s][i]);
            s = i;
        }
    }
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << " ";
    }
}
