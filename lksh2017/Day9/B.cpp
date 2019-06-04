#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int k = 4;
const int Ox[k] = {0, 0, 1, -1};
const int Oy[k] = {1, -1, 0, 0};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 2, vector<int>(m + 2, 1));
    vector<vector<int>> exits;

    for (int i = 1; i <= n; ++i) {
        for (int e = 1; e <= m; ++e) {
            cin >> g[i][e];
            if (g[i][e] == 2)
                exits.push_back({i, e});
        }
    }

    queue<vector<int>> q;
    vector<vector<int>> dist(n + 2, vector<int>(m + 2, 1e9));

    q.push({1, 1});
    dist[1][1] = 0;

    while (!q.empty()) {
        int vx = q.front()[0];
        int vy = q.front()[1];
        q.pop();

        for (int i = 0; i < k; ++i) {
            for (int l = 1; l < n + m; ++l) {
                int nx = vx + Ox[i] * l;
                int ny = vy + Oy[i] * l;
                if (dist[nx][ny] < dist[vx][vy] + 1) {
                    break;
                }
                if (g[nx][ny] == 2) {
                    dist[nx][ny] = dist[vx][vy] + 1;
                    break;
                }
                if (g[nx][ny] == 1) {
                    break;
                }
                if (g[nx + Ox[i]][ny + Oy[i]] == 1) {
                    dist[nx][ny] = dist[vx][vy] + 1;
                    q.push({nx, ny});
                    break;
                }
            }
        }
    }

    int ans = 1e9;
    for (auto i : exits)
        ans = min(dist[i[0]][i[1]], ans);

    cout << ans;
}
