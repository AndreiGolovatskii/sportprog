#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;

const int K = 4;
const int OX[K] = {0, 1, 0, -1};
const int OY[K] = {1, 0, -1, 0};
const int INF = 1e9;

int main() {
    //freopen("nolefts.in", "r", stdin);
    //freopen("nolefts.out", "w", stdout);
    int r, c;
    cin >> r >> c;

    vector<vector<char>> g(c, vector<char>(r));

    int dist[c][r][4];
    for (int i = 0; i < c; ++i) {
        for (int e = 0; e < r; ++e) {
            for (int k = 0; k < 4; ++k) {
                dist[i][e][k] = INF;
            }
        }
    }

    int fx = 0, fy = 0, sx = 0, sy = 0;
    for (int i = r - 1; i >= 0; --i) {
        cin.get();
        for (int e = 0; e < c; ++e) {
            cin.get(g[e][i]);
            if (g[e][i] == 'S') {
                sx = e;
                sy = i;
            }
            if (g[e][i] == 'F') {
                fx = e;
                fy = i;
            }
        }
    }

    queue<vector<int>> q;
    q.push({sx, sy, -1});

    while (!q.empty()) {
        int cx = q.front()[0];
        int cy = q.front()[1];
        int dir = q.front()[2];
        q.pop();
        if (dir == -1) {
            for (int i = 0; i < 4; ++i) {
                q.push({cx, cy, i});
                dist[cx][cy][i] = 0;
            }
        } else {
            for (int i = 0; i < 2; ++i) {
                int n_dir = (dir + i) % 4;
                int nx = cx + OX[n_dir];
                int ny = cy + OY[n_dir];
                if (g[nx][ny] != 'X' && dist[nx][ny][n_dir] > dist[cx][cy][dir] + 1) {
                    dist[nx][ny][n_dir] = dist[cx][cy][dir] + 1;
                    q.push({nx, ny, n_dir});
                }
            }
        }
    }
    cout << min(min(dist[fx][fy][1], dist[fx][fy][2]), min(dist[fx][fy][3], dist[fx][fy][0]));
}
