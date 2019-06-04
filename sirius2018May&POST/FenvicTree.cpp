#include <bits/stdc++.h>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>

const int MN = (int)1e5 + 5;
int tree[MN];

void add(int pos, int d) {
    for(; pos < MN; pos |= pos + 1) {
        tree[pos] += d;
    }
}
int get(int pos) {
    int res = 0;
    for(; pos >= 0; pos = (pos & (pos + 1)) - 1) {
        res += tree[pos];
    }
    return res;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
}