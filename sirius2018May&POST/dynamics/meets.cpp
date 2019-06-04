#include <bits/stdc++.h>

#define ll long long
#define pii pair<int, int>
#define x first
#define y second

using namespace std;

const int MN = 1 << 21;
const int MOD = (int)1e9 + 7;

int a[MN], b[MN], c[MN];
int dp[MN], p[MN];

int main(){
#ifndef ONLIN_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    dp[0] = 1;
    p[0] = 0;
    int mx = 0, pos = 0;
    for(int mask = 0; mask < MN; ++mask) {
        if(!dp[mask]) continue;
        bitset<20> curr(mask);
        int bal = k, cnt = 0;
        for(int i = 0; i < n; ++i) {
            if(curr[i]) {
                cnt++;
                bal += c[i];
            }
        }

        if(cnt > mx) {
            mx = cnt;
            pos = mask;
        }
        for(int i = 0; i < n; ++i) {
            if(!curr[i] && bal <= b[i] && bal >= a[i]) {
                auto cp = curr;
                cp[i] = 1;
                int ne = (int)cp.to_ulong();
                dp[ne] = 1;
                p[ne] = i;
            }
        }
    }

    cout << mx << "\n";
    vector<int> pref;
    while(pos != 0) {
        pref.push_back(p[pos]);
        bitset<20> bpos(pos);
        bpos[p[pos]] = 0;
        pos = (int)bpos.to_ulong();
    }
    reverse(pref.begin(), pref.end());

    for(auto i : pref) {
        cout << i + 1 << " ";
    }
}
