#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <fstream>

using namespace std;

const int Ox[3] = {1, 1, 0};
const int Oy[3] = {0, 1, 1};
const int n = 8;

int main() {
    //ifstream cin("recover.in");
    //ofstream cout("recover.out");
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = n - 1; i >=0; --i){
        for (int e = 0; e < n; ++e) {
            cin >> cost[e][i];
        }
    }

    vector<vector<int>> dist(n, vector<int>(n, 1e9));
    vector<vector<pair<int, int>>> prev(n, vector<pair<int, int>>(n));
    set<tuple<int, int, int>> Q;

    dist[0][0] = 0;
    Q.insert(make_tuple(dist[0][0], 0, 0));
    while (!Q.empty()) {
        int x = get<1>(*Q.begin());
        int y = get<2>(*Q.begin());
        Q.erase(Q.begin());
        for (int i = 0; i < 3; ++i) {
                int nx = x + Ox[i];
                int ny = y + Oy[i];
                if (nx < 0 || nx > 7 || ny < 0 || ny > 7)
                    continue;
                int len = cost[nx][ny];
                if (dist[x][y] + len < dist[nx][ny]) {
                    Q.erase(make_tuple(dist[nx][ny], nx, ny));
                    dist[nx][ny] = dist[x][y] + len;
                    prev[nx][ny] = {x, y};
                    Q.insert(make_tuple(dist[nx][ny], nx, ny));
                }
        }
    }

    stack<pair<int, int>> ans;
    ans.push({7, 7});
    while (ans.top() != make_pair(0, 0)) {
        ans.push(prev[ans.top().first][ans.top().second]);
    }

    cout << dist[7][7] << "\n";
    while (!ans.empty()) {
        char x = 'a' + ans.top().first;
        char y = '1' + ans.top().second;
        cout << x << y <<" ";
        ans.pop();
    }
}
