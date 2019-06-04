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

int main() {
    ifstream cin("recover.in");
    ofstream cout("recover.out");

    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(2, vector<int>(n + 1, 0));
    dp[1][0] = 1;

    for (int i = 0; i < n; ++i) {
        int k = 0;

        swap(dp[k], dp[k + 1]);
        dp[k + 1].clear();
        dp[k + 1].resize(n + 1, 0);

        for (int bal = 0; bal < n; ++bal) {
            if (s[i] == '(') {
                dp[k + 1][bal + 1] = dp[k][bal];
            } else if (s[i] == ')' && bal > 0) {
                dp[k + 1][bal - 1] = dp[k][bal];
            } else {
                dp[k + 1][bal + 1] = dp[k][bal];
                if (bal > 0) {
                    dp[k + 1][bal - 1] += dp[k][bal];
                    dp[k + 1][bal - 1] = dp[k + 1][bal - 1] % MOD;
                }
            }
        }
    }
    cout << dp[1][0];
}
