#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int N = 65;

const int K = 4;

const int OX[K] = {1, 0, -1, 0}; //east, south, west, north
const int OY[K] = {0, -1, 0, 1};
const string DESC[K] = {"EAST", "SOUTH", "WEST", "NORTH"};

bool used[N][N];
int cnt_empty = 0;
int cnt_sum = 1;

bool comand(int k) {
    cout << DESC[k] << endl;
    cout.flush();
    string ans;
    cin >> ans;
    return !(ans == "SWAMP");
}

void dfs(int x, int y, int prev) {
    used[x][y] = true;
    cnt_empty++;
    for (int i = 0; i < K; ++i) {
        int nx = x + OX[i];
        int ny = y + OY[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
            continue;
        }
        if (!used[nx][ny]) {
            cnt_sum++;
            if (comand(i)) {
                dfs(nx, ny, (i + 2) % 4);
            } else {
                used[nx][ny] = true;
            }
        }
    }
    if (cnt_sum == N * N) {
        return;
    }
    comand(prev);
}

int main() {
    dfs(32, 32, 0);
    cout << N * N - cnt_empty;
}