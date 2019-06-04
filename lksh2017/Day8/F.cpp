#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cstdlib>
#include <algorithm>


using namespace std;

const int M = 16, N = 7;

const int K = 8;
const int OX[K] = {2, 2, 1, -1, 1, -1, -2, -2};
const int OY[K] = {1, -1, 2, 2, -2, -2, 1, -1};

vector<vector<bool>> used(M, vector<bool>(N, false));
vector<vector<vector<int>>> n_prev(M, vector<vector<int>>(N, vector<int>(2)));
vector<vector<int>> pr;


int get_variable(int x, int y) {
    int ans = 0;
    for (int i = 0; i < K; ++i) {
        int nx = x + OX[i];
        int ny = y + OY[i];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N || used[nx][ny])
            continue;
        else
            ans ++;
    }
    return ans;
}

vector<int> get_Q(int x, int y) {
    vector<pair<int, int>> ans;
    for (int i = 0; i < K; ++i) {
        int nx = x + OX[i];
        int ny = y + OY[i];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N ||used[nx][ny])
            continue;
        ans.push_back({get_variable(nx, ny), i});
    }
    sort(ans.begin(), ans.end());
    vector<int> ans1;
    for (auto &i : ans)
        ans1.push_back(i.second);
    return ans1;
}
void print_ans() {
    for (auto &i : pr) {
        char x = 'a' + i[0];
        int y = 1 + i[1];
        cout << x << y << "\n";
    }
    exit(0);
}
bool check(vector<int> A, vector<int> B) {
    int x1 = A[0];
    int y1 = A[1];
    int x2 = B[0];
    int y2 = B[1];
    for (int i = 0; i < K; ++i) {
        int nx = x1 + OX[i];
        int ny = y1 + OY[i];
        if (nx == x2 && ny == y2)
            return true;
    }
    return false;
}

void dfs(int xc, int yc) {
    used[xc][yc] = true;
    vector<int> Q = get_Q(xc, yc);
    for (auto &i : Q) {
        int nx = xc + OX[i];
        int ny = yc + OY[i];
        pr.push_back({nx, ny});
        dfs(nx, ny);
    }
    if (pr.size() == N * M && check(*pr.begin(), *pr.rbegin()))
        print_ans();
    pr.erase(--pr.end());
    used[xc][yc] = false;
}

int main() {
    int xs = 3, ys = 3;
    pr.push_back({xs, ys});
    dfs(xs, ys);
}
