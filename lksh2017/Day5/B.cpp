#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<long long> Ans(n + 1, 0);
    vector<long long> C(n + 1, 0);
    Ans[0] = 1;
    C[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        for (int k = 0; k < i; ++k) {
            C[i] += C[k] * C[i - k - 1];
            C[i] = C[i] % MOD;
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        for (int k = 0; k < i; ++k) {
            Ans[i] += Ans[k] * Ans[i - k - 1] + C[k] * Ans[i - k - 1];
            Ans[i] = Ans[i] % MOD;
        }
    }
    cout << Ans[n];
}
