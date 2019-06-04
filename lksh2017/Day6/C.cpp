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
    ifstream cin("build.in");
    ofstream cout("build.out");

    int n, k;
    cin >> n >> k;
    n *= 2;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int bal = 0; bal < n; ++bal) {
            dp[i + 1][bal + 1] = dp[i][bal];
            if (bal > 0) {
                dp[i + 1][bal - 1] += dp[i][bal];
            }
        }
    }

    string s;
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[n - i - 1][bal + 1] < k) {
            s += ')';
            k -= dp[n - i - 1][bal + 1];
            bal--;
        }
        else {
            s += '(';
            bal++;
        }
    }

    cout << s;
}
