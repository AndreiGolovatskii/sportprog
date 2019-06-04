#include <vector>
#include <iostream>
#include <cstdlib>
#include <map>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
    cout.precision(10);
    cout << fixed;
    int n, k;
    cin >> k >> n;
    vector<int> ks(k);
    for (int i = 0; i < k; ++i) {
        cin >> ks[i];
    }
    vector<int> ns(n);
    for (int i = 0; i < n; ++i) {
        cin >> ns[i];
    }
    vector<int> sum(k + 1, 0);
    for (int i = 1; i <= k; ++i) {
        sum[i] = sum[i-1] + ks[i - 1];
    }
    set<int> sts;
    for (int m = 1; m <= k; ++m){
        sts.insert(ns[0] - sum[m]);
    }
    int ans = 0;
    for (auto d : sts) {
        map<int, bool> p;
        for (int i = 1; i <= k; ++i) {
            p[d + sum[i]] = true;
        }
        bool f = true;
        for (auto i : ns) {
            if (p[i] == false)
                f = false;
        }
        if (f) {
            ans++;
        }
    }
    cout << ans;
}

