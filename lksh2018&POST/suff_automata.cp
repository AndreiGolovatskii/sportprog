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

#pragma optimize( "", on)

using namespace std;
const int ALPH = 27, MN = 4000, MK = 1000;

struct node{
    int_fast16_t suff, len;
    char nel[ALPH], nelit;
    int_fast16_t ne[ALPH];
    node(){};
    node(int len, int suff, int e, int nelit):len(len), nelit(nelit), suff(suff) {
        if(!e) {
            memset(ne, 0, sizeof(ne));
        }
    };
};
int tit, cur, root;
node t[2 * MK + 7];

inline int addnode(int len, int suff, int e = 0, int nelit = 0) {
    t[tit] = node(len, suff, e, nelit);
    return tit++;
}
inline int nodecopy(int n, int len) {
    int cp = addnode(len, t[n].suff, 1, t[n].nelit);
    
    memcpy(t[cp].ne, t[n].ne, sizeof(t[n].ne));
    memcpy(t[cp].nel, t[n].nel, sizeof(t[n].nel[0]) * t[n].nelit);
    return cp;
}
inline void init(){
    tit = 1;
    root = addnode(0, -1);
    cur = root;
}
inline void addnec(int n, int c) {
    auto &k = t[n];
    k.nel[k.nelit++] = c;
}

inline void addchar(char c) {
    int nn = addnode(t[cur].len + 1, -1);
    while(cur != -1 && !t[cur].ne[c]) {
        t[cur].ne[c] = nn;
        addnec(cur, c);
        cur = t[cur].suff;
    }
    if(cur != -1) {
        int q = t[cur].ne[c];
        if(t[q].len == t[cur].len + 1) {
            t[nn].suff = q;
        } else {
            int cq = nodecopy(q, t[cur].len + 1);
            t[nn].suff = t[q].suff = cq;
            while(cur != -1 && t[cur].ne[c] == q) {
                t[cur].ne[c] = cq;
                cur = t[cur].suff;
            }
        }
    } else {
        t[nn].suff = root;
    }
    cur = nn;
}
int dp[2 * MK];
inline int gt(int a) {
    if(dp[a] != -1) return dp[a];
    int r = 1;
    
    auto &k = t[a];
    
    for(int i = 0; i < k.nelit; ++i) {
        r += gt(k.ne[k.nel[i]]);
    }
    return dp[a] = r;
}
inline int getans(){
    memset(dp, -1, sizeof(dp[0]) * tit);
    for(int i = cur; i >= root; --i) {
        gt(i);
    }
    return dp[root] - 1;
}

char s[MN + MK + 7];
int main() {
    auto ts = clock();
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    
    int k;
    scanf("%d ", &k);
    gets(s);
    int n = (int)strlen(s);
    memcpy(s + n, s, sizeof(s[0]) * k);
    
    for(int i = 0; i < n; ++i) {
        init();
        for(int j = 0; j < k; ++j) {
            addchar(s[i + j] - 'a');
        }
        printf("%d ", getans());
    }
    
    cerr << "My_sol :" << ((double)clock() - ts) / CLOCKS_PER_SEC << " Sec,\n";
}
