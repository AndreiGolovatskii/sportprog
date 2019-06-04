#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 8;
const int OX[N] = {2, 2, 1, -1, 1, -1, -2, -2};
const int OY[N] = {1, -1, 2, 2, -2, -2, 1, -1};

vector<int> g_prev[N][N][N][N];
bool used[N][N][N][N];

vector<vector<int>> dp(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4) {
    used[x1][y1][x2][y2] = true;

    queue<vector<int>> q;
    q.push({x1, y1, x2, y2});

    while (!q.empty()) {
        int x1 = q.front()[0];
        int y1 = q.front()[1];
        int x2 = q.front()[2];
        int y2 = q.front()[3];
        q.pop();

        for (int k = 0; k < N; ++k) {
            int nx = x1 + OX[k];
            int ny = y1 + OY[k];
            if (!(nx < 0 || nx >= N || ny < 0 || ny >= N || (nx == x2 && ny == y2))) {
                if (!used[nx][ny][x2][y2]) {
                    used[nx][ny][x2][y2] = true;
                    q.push({nx, ny, x2, y2});
                    g_prev[nx][ny][x2][y2] = {x1, y1, x2, y2};
                }
            }
            nx = x2 + OX[k];
            ny = y2 + OY[k];
            if (!(nx < 0 || nx >= N || ny < 0 || ny >= N || (nx == x1 && ny == y1))) {
                if (!used[x1][y1][nx][ny]) {
                    used[x1][y1][nx][ny]  = true;
                    q.push({x1, y1, nx, ny});
                    g_prev[x1][y1][nx][ny] = {x1, y1, x2, y2};
                }
            }
        }
    }
    vector<vector<int>> ans;
    ans.push_back({x3, y3, x4, y4});
    int nx3 = x3, nx4 = x4, ny3 = y3, ny4 = y4;
    while (true) {
        auto p = g_prev[nx3][ny3][nx4][ny4];

        nx3 = p[0];
        ny3 = p[1];
        nx4 = p[2];
        ny4 = p[3];
        ans.push_back({nx3, ny3, nx4, ny4});
        if (nx3 == x1 && nx4 == x2 && ny3 == y1 && ny4 == y2)
            break;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}



vector<int> get_in() {
    string s;
    vector<int> in(8);
    cin >> s;
    in[0] = s[0] - 'a';
    in[1] = s[1] - '1';
    return in;
}


int main() {
    vector<int> ix;
    vector<int> iy;
    for (int i = 0; i < 4; ++i) {
        vector<int> a;
        a = get_in();
        ix.push_back(a[0]);
        iy.push_back(a[1]);
    }
    if (ix[0] == ix[2] && ix[1] == ix[3] && iy[0] == iy[2] && iy[1] == iy[3])
        return 0;

    vector<vector<int>> ans = dp(ix[0], ix[1], ix[2], ix[3], iy[0], iy[1], iy[2], iy[3]);

    for (size_t i = 1; i < ans.size(); ++i) {
        if (ans[i][1] != ans[i - 1][1]) {
            char x = 'a' + ans[i][0];
            char y = '1' + ans[i][1];
            cout << 1 << " " << x << y << "\n";
        } else {
            char x = 'a' + ans[i][2];
            char y = '1' + ans[i][3];
            cout << 2 << " " << x << y << "\n";
        }
    }
}