#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int INF = 1e9;
const int N = 5;

const int K = 4;

const int OX[K] = {1, 0, -1, 0}; //east, south, west, north
const int OY[K] = {0, -1, 0, 1};
const string DESC[K] = {"EAST", "SOUTH", "WEST", "NORTH"};

bool used[N][N];
int cnt = 0;

bool comand(int k) {
    cout << DESC[k] << endl;
    cout.flush();
    string ans;
    cin >> ans;
    if (ans == "SWAMP") {
        return false;
    } else {
        return true;
    }

}

void dfs(int x, int y, int prev) {
    used[x][y] = true;
    cerr << "curr_pos" << x << " " << y << endl;
    cnt++;
    for (int i = 0; i < K; ++i) {
        int nx = x + OX[i];
        int ny = y + OY[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
            continue;
        }
        if (!used[nx][ny] && comand(i)) {
            dfs(nx, ny, (i + 2) % 4);
        }
    }
    comand(prev);
}

int main() {
    //dfs(32, 32, 0);
    dfs (2, 2, 0);
    cout << N * N - cnt;
    int k = 0;
}