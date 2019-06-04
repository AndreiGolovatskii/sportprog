#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

const int n = 8;
const int Ox[n] = {2, 2, 1, -1, 1, -1, -2, -2};
const int Oy[n] = {1, -1, 2, 2, -2, -2, 1, -1};

vector<int> g_prev[n][n][n][n];
bool used[n][n][n][n][2];


vector<vector<int>> dp(int flag, int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4) {
    int f = flag % 2;

    used[x1][y1][x2][y2][f] = true;

    queue<vector<int>> Q;
    Q.push({x1, y1, x2, y2, flag});

    while (!Q.empty()) {
        int x1 = Q.front()[0];
        int y1 = Q.front()[1];
        int x2 = Q.front()[2];
        int y2 = Q.front()[3];
        int flag = Q.front()[4];
        Q.pop();

        if (flag == 1) {
            for (int k = 0; k < n; ++k) {
                int nx = x1 + Ox[k];
                int ny = y1 + Oy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n || (nx == x2 && ny == y2))
                    continue;
                if (!used[nx][ny][x2][y2][f]) {
                    used[nx][ny][x2][y2][f] = true;
                    Q.push({nx, ny, x2, y2, 2});
                    g_prev[nx][ny][x2][y2] = {x1, y1, x2, y2};
                }
            }
        } else {
            for (int k = 0; k < n; ++k) {
                int nx = x2 + Ox[k];
                int ny = y2 + Oy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n || (nx == x1 && ny == y1))
                    continue;
                if (!used[x1][y1][nx][ny][f]) {
                    used[x1][y1][nx][ny][f]  = true;
                    Q.push({x1, y1, nx, ny, 1});
                    g_prev[x1][y1][nx][ny] = {x1, y1, x2, y2};
                }
            }
        }
    }
    vector<vector<int>> ans;
    ans.push_back({x3, y3, x4, y4});
    int nx3 = x3, nx4 = x4, ny3 = y3, ny4 = y4;
    for(;;) {
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

    cin >> s;
    in[2] = s[0] - 'a';
    in[3] = s[1] - '1';

    cin >> s;
    in[4] = s[0] - 'a';
    in[5] = s[1] - '1';

    cin >> s;
    in[6] = s[0] - 'a';
    in[7] = s[1] - '1';
    return in;
}


int main() {
    vector<int> in = get_in();
    int x1 = in[0];
    int y1 = in[1];

    int x2 = in[2];
    int y2 = in[3];

    int x3 = in[4];
    int y3 = in[5];

    int x4 = in[6];
    int y4 = in[7];

    if (x1 == x3 && x2 == x4 && y1 == y3 && y2 == y4)
        return 0;

    auto ans = dp(1, x1, x2, x3, x4, y1, y2, y3, y4);
    auto ans1 = dp(2, x1, x2, x3, x4, y1, y2, y3, y4);

    if (ans1.size() < ans.size())
        swap(ans1, ans);

    for (size_t i = 1; i < ans.size(); ++i) {
        if(ans[i][1] != ans[i - 1][1]) {
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
