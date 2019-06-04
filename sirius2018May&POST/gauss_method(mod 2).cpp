#include <bits/stdc++.h>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>
#define val bitset<MN>

const int MN = 251;
inline val operator+(const val &a, const val &b) {
    return (a | b) & (a ^ b);
}
inline const bool sum(const bool &a, const bool &b) {
    return (a | b) & (a ^ b);
}
bool gauss(vector<val> &MT, int n, val &ans){
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(MT[j][i] == 1) {
                swap(MT[j], MT[i]);
            }
        }
        if(MT[i][i] == 0) {
            return false;
        }

        for(int j = i + 1; j < n; ++j) {
            if(MT[j][i] == 1) {
                MT[j] = MT[j] + MT[i];
            }
        }
    }
    ans[n] = 1;
    for(int i = n - 1; i >= 0; --i) {
        ans[i] = (MT[i] & ans).count() & 1;
    }
    return true;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<val> MT(n);
    for(int i = 0; i < n; ++i) {
        for(;;) {
            int c;
            cin >> c;
            if(c == -1) break;
            c--;
            MT[c][i] = 1;
        }
        MT[i][n] = 1;
    }

    val ans;
    if(!gauss(MT, n, ans)) {
        cout << "No solution\n";
        return 0;
    }
    for(int i = 0; i < n; ++i) {
        if(ans[i])
            cout << i + 1 << " ";
    }
}#include <bits/stdc++.h>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>
#define val bitset<MN>

const int MN = 251;
inline val operator+(const val &a, const val &b) {
    return (a | b) & (a ^ b);
}
inline const bool sum(const bool &a, const bool &b) {
    return (a | b) & (a ^ b);
}
bool gauss(vector<val> &MT, int n, val &ans){
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            if(MT[j][i] == 1) {
                swap(MT[j], MT[i]);
            }
        }
        if(MT[i][i] == 0) {
            return false;
        }

        for(int j = i + 1; j < n; ++j) {
            if(MT[j][i] == 1) {
                MT[j] = MT[j] + MT[i];
            }
        }
    }
    ans[n] = 1;
    for(int i = n - 1; i >= 0; --i) {
        ans[i] = (MT[i] & ans).count() & 1;
    }
    return true;
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<val> MT(n);
    for(int i = 0; i < n; ++i) {
        for(;;) {
            int c;
            cin >> c;
            if(c == -1) break;
            c--;
            MT[c][i] = 1;
        }
        MT[i][n] = 1;
    }

    val ans;
    if(!gauss(MT, n, ans)) {
        cout << "No solution\n";
        return 0;
    }
    for(int i = 0; i < n; ++i) {
        if(ans[i])
            cout << i + 1 << " ";
    }
}