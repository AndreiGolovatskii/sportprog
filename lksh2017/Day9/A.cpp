#include <iostream>
#include <map>
#include <vector>
#include <cstdio>

using namespace std;

const int N = 11;

const int K = 4;
const int OX[K] = {0, 0, 1, -1};
const int OY[K] = {1, -1, 0, 0};

char g[N][N];
bool used[N][N];

int dfs(int vx, int vy) {
    used[vx][vy] = true;
    int ans = 1;
    for (int i = 0; i < K; ++i) {
        int nx = vx + OX[i];
        int ny = vy + OY[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
            continue;
        }
        if (!used[nx][ny] && g[nx][ny] == g[vx][vy]) {
            ans += dfs(nx, ny);
        }
    }
    return ans;
}

int main() {
    //freopen("balls.in", "r", stdin);
    //freopen("balls.out", "w", stdout);

    for (int i = 0; i < N; ++i) {
        for (int e = 0; e < N; ++e) {
            cin >> g[i][e];
        }
    }

    map<short, int> ans;

    for (int i = 0; i < N; ++i) {
        for (int e = 0; e < N; ++e) {
            if (!used[i][e]) {
                int c = dfs(i, e);
                ans[g[i][e]] = max(ans[g[i][e]], c * (c - 1));
            }
        }
    }

    cout << "R: " << ans['R'] << endl;
    cout << "G: " << ans['G'] << endl;
    cout << "B: " << ans['B'] << endl;
    cout << "Y: " << ans['Y'] << endl;
    cout << "V: " << ans['V'] << endl;
}
