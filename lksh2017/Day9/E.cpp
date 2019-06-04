#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

const int K = 4;
const int OX[K] = {1, 0, -1, 0};
const int OY[K] = {0, -1, 0, 1};
const char DESC[K] = {'E', 'N', 'W', 'S'};
const int INF = (const int) 1e9;

int main() {
    freopen("civ.in", "r", stdin);
    freopen("civ.out", "w", stdout);
    int n, m, sx, sy, fx, fy;
    cin >> n >> m >> sy >> sx >> fy >> fx;

    vector<vector<int>> map(m + 2, vector<int>(n + 2, INF));
    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= m; ++x) {
            char  a;
            cin >> a;
            if (a == '.') {
                map[x][y] = 1;
            } else if (a == 'W'){
                map[x][y] = 2;
            }
        }
    }
    vector<vector<int>> dist(m + 2, vector<int>(n + 2, INF));
    vector<vector<int>> pr(m + 2, vector<int>(n + 2, -1));
    dist[sx][sy] = 0;

    set<vector<int>> q;

    q.insert({dist[sx][sx], sx, sy});

    while (!q.empty()) {
        int vx = (*q.begin())[1];
        int vy = (*q.begin())[2];
        q.erase(q.begin());
        for (int i = 0; i < K; ++i) {
            int nx = vx + OX[i];
            int ny = vy + OY[i];
            int w = map[nx][ny];
            if (w == INF) {
                continue;
            }
            if (dist[vx][vy] + w < dist[nx][ny]) {
                q.erase({dist[nx][ny], nx, ny});
                dist[nx][ny] = dist[vx][vy] + w;
                pr[nx][ny] = i;
                q.insert({dist[nx][ny], nx, ny});
            }
        }
    }

    if (dist[fx][fy] == INF) {
        cout << -1;
        return 0;
    }

    cout << dist[fx][fy] << endl;

    vector<char > ans;
    int curr = pr[fx][fy];
    while (curr != -1) {
        ans.push_back(DESC[curr]);
        curr = (curr + 2) % 4;
        fx += OX[curr];
        fy += OY[curr];
        curr = pr[fx][fy];
    }
    reverse(ans.begin(), ans.end());

    for (auto i : ans) {
        cout << i;
    }
}
