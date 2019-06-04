#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

const int Ox[8] = {2, 2, 1, -1, 1, -1, -2, -2};
const int Oy[8] = {1, -1, 2, 2, -2, -2, 1, -1};
const int n = 8;

int main() {
    //ifstream cin("check.in");
    //ofstream cout("check.out");
    string s;
    cin >> s;
    int x1 = s[0] - 'a';
    int y1 = s[1] - '1';

    cin >> s;
    int x2 = s[0] - 'a';
    int y2 = s[1] - '1';

    deque<pair<int, int>> Q;
    Q.push_back({x1, y1});

    vector<vector<int>> ans(8, vector<int>(8, 1e9));
    vector<vector<pair<int, int>>> prev(8, vector<pair<int, int>>(8, {0, 0}));

    ans[x1][y1] = 0;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop_front();
        for (int i = 0; i < n; ++i) {
                int nx = x + Ox[i];
                int ny = y + Oy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                    continue;

                if (ans[nx][ny] > ans[x][y] + 1) {
                    ans[nx][ny] = ans[x][y] + 1;
                    Q.push_back({nx, ny});
                    prev[nx][ny] = {x, y};
                }
        }
    }
    Q.push_back({x2, y2});

    while (x2 != x1 || y2 != y1) {
        Q.push_back(prev[x2][y2]);
        auto k =prev[x2][y2];
        x2 = k.first;
        y2 = k.second;
    }
    while (!Q.empty()) {
        char x = 'a' + Q.back().first;
        char y = '1' + Q.back().second;
        cout << x << y <<"\n";
        Q.pop_back();
    }
}
