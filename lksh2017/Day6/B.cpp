#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

const int MOD = 1e9 + 7;

int count_sq(int n, int p) {
    vector<vector<int>> dp(2, vector<int>(n + 1));
    dp[1][0] = 1;
    for (int i = 0; i < n; ++i) {
        int k = 0;

        swap(dp[k], dp[k + 1]);
        dp[k + 1].clear();
        dp[k + 1].resize(n + 1, 0);

        for (int bal = 0; bal < n; ++bal) {
            if (bal < p)
                dp[k + 1][bal + 1] = dp[k][bal];
            if (bal > 0) {
                dp[k + 1][bal - 1] += dp[k][bal];
                dp[k + 1][bal - 1] = dp[k + 1][bal - 1] % MOD;
            }
        }
    }
    return dp[1][0];
}

int main() {
    //ofstream cout("recover.out");
    //ifstream cin("recover.in");
    int n, k;
    cin >> n >> k;
    n *= 2;
    cout << (count_sq(n, k) - count_sq(n, k - 1) + MOD) % MOD;
}
