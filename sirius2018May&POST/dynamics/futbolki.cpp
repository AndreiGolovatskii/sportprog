#include <bits/stdc++.h>

#define ll long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int MN = 2000 + 10;
const ll MOD = (int)1e9;

ll dp[MN][MN], in[MN];

int main(){
#ifndef ONLIN_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> in[i];
    }

    for(int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    for(int len = 1; len < n; ++len) {
        for(int i = 0; i + len < n; ++i){
            int j = i + len;
            if (in[i] == in[j]) {
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + 1;
                dp[i][j] %= MOD;
            } else {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1]) % MOD - dp[i + 1][j - 1] + MOD;
                dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[0][n - 1];
}

