#include <set>
#include <cstdio>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <random>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <list>
#include <bitset>

#pragma optimize("", on)

#define ll long long

using namespace std;


int bp(int n, int p, int m) {
    if(p == 1) return n;
    if(p == 0) return 1;
    if(p & 1) {
        return (n * bp(n, p - 1, m)) % m;
    } else {
        int a = bp(n, p >> 1, m);
        return (a * a) % m;
    }
}
const int MN = 1e5 + 3;

const int plist[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int PS = 15;

int r[PS][PS], x[PS], tpmode[MN][PS], a[PS], val[MN];
void init(){
    for(int i = 0; i < PS; ++i) {
        for(int j = i + 1; j < PS; ++j) {
            r[i][j] = bp(plist[i], plist[j] - 2, plist[j]);
        }
    }
    for(int j = 0; j < PS; ++j) {
        tpmode[0][j] = 1;
    }
    for(int i = 1; i < MN; ++i) {
        for(int j = 0; j < PS; ++j) {
            tpmode[i][j] = (tpmode[i - 1][j] * 10) % plist[j];
        }
    }
}
void initnum(const string &s) {
    int n = (int)s.size();
    for(int i = 0; i < n; ++i) {
        val[i] = s[i] - '0';
        for(int j = 0; j < PS; ++j) {
            a[j] += (val[i] * tpmode[i][j]) % plist[j];
        }
    }
}
void change(int pos, int nv) {
    pos--;
    for(int i = 0; i < PS; ++i) {
        a[i] -= (val[pos] * tpmode[pos][i]) % plist[i];
        if(a[i] < 0) a[i] += plist[i];
        a[i] += (nv * tpmode[pos][i]);
        if(a[i] >= plist[i]) a[i] %= plist[i];
    }
    val[pos] = nv;
}

void calcx(const bitset<PS> &ign){
    for(int i = 0; i < PS; ++i) {
        if(ign[i]) continue;
        x[i] = a[i];
        for(int j = 0; j < i; ++j) {
            if(ign[j]) continue;
            x[i] = (x[i] - x[j]) * r[j][i];
            x[i] %= plist[i];
            if(x[i] < 0) x[i] += plist[i];
        }
    }
}


ll get(ll mod) {
    if(mod == 1) {
        return 0;
    }
    bitset<PS> ign;
    for(int i = 0; i < PS; ++i) {
        if(mod % plist[i]) {
            ign[i] = 1;
        }
    }
    
    calcx(ign);
    
    ll pp = 1, ans = 0;
    for(int i = 0; i < PS; ++i) {
        if(ign[i]) continue;
        ans += x[i] * pp;
        ans %= mod;
        pp *= plist[i];
    }
    return ans;
}

int main() {
    auto ts = clock();
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    init();
    
    string num;
    cin >> num;
    reverse(num.begin(), num.end());
    
    initnum(num);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        if(t) {
            int k, b;
            cin >> k >> b;
            change(k, b);
        } else {
            ll c;
            cin >> c;
            cout << get(c) << "\n";
        }
    }
    
    cerr << "My_sol :" << ((double)clock() - ts) / CLOCKS_PER_SEC << " Sec,\n";
}
