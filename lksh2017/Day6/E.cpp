#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

int main() {
    string s;
    cin >> s;
    size_t n = s.size();
    vector<vector<int>> dp(n + 1, vector<int> (n + 1, 1e9));
    for (int i = 0; i <= n; ++i)
        dp[i][i] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = n - len -1; i >= 0 ; --i) {
            int j = i + len;
            dp[i][j] = 1e9;
            for (int k = 0; k < i; ++k) {
                dp[i][j] = min(dp[i][j], dp[i + 1][i + k] + dp[i + k + 2][j]);
            }
        }
    }
    cout << dp[0][n - 1];
}
