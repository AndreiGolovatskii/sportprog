#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;
#define pii pair<int, int>
#define x first
#define y second

const int MN = 100 + 7, MT = 2000 + 7;
vector<int> g[MN + MT + 7];
int F[MN + MT + 7][MN + MT + 7], T[MN + MT + 7][MN + MT + 7];


int codeN(int t) {
    return t + 1;
}

int codeT(int t) {
    return t + MN;
}

int s = 0, f = codeT(MT);
vector<int> used;
int dfs(int u, int cm) {
    if(u == f) return cm;
    used[u] = 1;
    for(auto v : g[u]) {
        if(!used[v] && F[u][v] < T[u][v]) {
            int d = dfs(v, min(cm, T[u][v] - F[u][v]));
            if(d > 0) {
                F[u][v] += d;
                F[v][u] -= d;
                return d;
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        T[0][codeN(i)] = 2;
        g[0].push_back(codeN(i));
        g[codeN(i)].push_back(0);
    }
    for(int i = 0; i < MT; ++i) {
        T[codeT(i)][f] =  k;
        g[codeT(i)].push_back(f);
        g[f].push_back(codeT(i));
    }
    for(int i = 0; i < n; ++i) {
        int s, t;
        cin >> s >> t;
        for(int j = s; j < s + t; ++j) {
            g[codeN(i)].push_back(codeT(j));
            g[codeT(j)].push_back(codeN(i));
            T[codeN(i)][codeT(j)] = 1;
        }
    }
    int ans = 0;
    while (true) {
        used.assign(MN + MT + 7, 0);
        int d = dfs(s, 1e9);
        if(!d) break;
        ans += d;
    }
    if(ans != n * 2) {
        cout << "No\n";
        return 0;
    } else {
        cout << "Yes\n";
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < MT; ++j) {
                if(F[codeN(i)][codeT(j)]) {
                    cout << j << " ";
                }
            }
            cout << "\n";
        }
    }
}

