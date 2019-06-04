#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;

void dfs(int v, vector<bool> &used, vector<vector<int>> &g, int wt, bool rev) {
    used[v] = true;
    for (int i = 0; i < n; ++i) {
        if (!used[i] && g[v][i] <= wt && rev) {
            dfs(i, used, g, wt, rev);
        } else if (!used[i] && g[i][v] <= wt && !rev) {
            dfs(i, used, g, wt, rev);
        }
    }
}

bool check(vector<bool> a) {
    for (auto i : a) {
        if (!i)
            return false;
    }
    return true;
}


int main() {
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    int max_s = 0;
    for (int i = 0; i < n; ++i) {
        for (int e = 0; e < n; ++e) {
            cin >> g[i][e];
            max_s = max(max_s, g[i][e]);
        }
    }
    int left = 0;
    int right = max_s;
    for (int i = 0; i < 50; ++i) {
        int mid = (left + right) / 2;
        vector<bool> v1(n, false);
        vector<bool> v2(n, false);
        dfs(0, v1, g, mid, true);
        dfs(0, v2, g, mid, false);
        if (check(v1) && check(v2)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    cout << right;
}
