#include <set>
#include <cstdio>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <math.h>
#include <random>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <list>
#include <bitset>
#include <deque>
#include <complex>
#include <cmath>

#define ll long long
#define x first
#define y second
#define pii pair<int, int>

using namespace std;
const int HS = 50000 + 17;

struct hmap{
    struct node{
        node *ne;
        ll key, val;
        node(){};
        node(node *ne, ll key, ll val):ne(ne), key(key), val(val){};
    };
    node *t[HS];
    
    ll &operator[](int k) {
        node* c = t[k % HS];
        while(c != 0) {
            if(c->key == k) {
                return c->val;
            } else {
                c = c->ne;
            }
        }
        
        int km = k % HS;
        c = new node(t[km], k, 0);
        t[km] = c;
        return c->val;
    }
    
    hmap(){
        memset(t, 0, sizeof(t));
    };
};

const int MN = 12;
int n, m;
inline bool isfree(int x, int y) {
    return x < n && y < m;
}

#define state int
inline int gv(state a, int pos) {
    return (a >> (pos + pos)) & 3;
}
inline int sv(state a, int pos, int val) {
    pos <<= 1;
    return (a & ((((1 << pos) - 1)) + (INT32_MAX << (pos + 2)))) + (val << pos) ;
}

hmap nextdp, curdp;
hmap used;
queue<state> nextQ, curQ;
void add(int cur, ll fr, int i, int j) {
    if(j == m - 1) {
        cur <<= 2;
    }
    if(used[cur] != i * m + j + 1) {
        nextdp[cur] = fr;
        nextQ.push(cur);
        used[cur] = i * m + j + 1;
    } else {
        nextdp[cur] += fr;
    }
}
bool ctoo(int &cur, int j) {
    int st = 0;
    for(int i = j + 1; i <= m; ++i) {
        int t = gv(cur, i);
        if(!t) continue;
        if(t == 1) {
            st++;
        } else {
            if(st) {
                st--;
            } else {
                cur = sv(cur, i, 1);
                return 1;
            }
        }
    }
    return 0;
}

bool otoc(int &cur, int j) {
    int st = 0;
    for(int i = j; i >= 0; --i) {
        int t = gv(cur, i);
        if(!t) continue;
        if(t == 2) {
            st++;
        } else {
            if(st) {
                st--;
            } else {
                cur = sv(cur, i, 2);
                return 1;
            }
        }
    }
    return 0;
}

int32_t main() {
    auto ts = clock();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    if(m > n) swap(m, n);
    pii last = {n - 1, m - 1};
    state start = 0;
    nextdp[start] = 1;
    nextQ.push(start);
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            swap(nextQ, curQ);
            swap(nextdp, curdp);
            while(curQ.size()) {
                state cur = curQ.front();
                curQ.pop();
                
                ll cv = curdp[cur];
                if(!isfree(i, j)) {
                    if(gv(cur, j) || gv(cur, j + 1)) {
                        continue;
                    } else {
                        add(cur, cv, i, j);
                    }
                } else {
                    if(gv(cur, j) && gv(cur, j + 1)) {
                        if(i == last.x && j == last.y) {
                            ans += cv;
                        } else if(gv(cur, j) == 1 && gv(cur, j + 1) == 2) {
                            continue;
                        } else if(gv(cur, j) == 2 && gv(cur, j + 1) == 1){
                            cur = sv(cur, j, 0);
                            cur = sv(cur, j + 1, 0);
                            
                            add(cur, cv, i, j);
                        }else if(gv(cur, j) == 1 && gv(cur, j + 1) == 1){
                            cur = sv(cur, j, 0);
                            cur = sv(cur, j + 1, 0);
                            
                            if(ctoo(cur, j))
                                add(cur, cv, i, j);
                        } else {
                            cur = sv(cur, j, 0);
                            cur = sv(cur, j + 1, 0);
                            
                            if(otoc(cur, j))
                                add(cur, cv, i, j);
                        }
                    } else if(!gv(cur, j) && !gv(cur, j + 1)) {
                        if(!isfree(i, j + 1)) continue;
                        if(!isfree(i + 1, j)) continue;
                        cur = sv(cur, j, 1);
                        cur = sv(cur, j + 1, 2);
                        
                        add(cur, cv, i, j);
                    } else if(gv(cur, j)){
                        int t = gv(cur, j);
                        if(isfree(i, j + 1)) {
                            int nv = sv(cur, j, 0);
                            nv = sv(nv, j + 1, t);
                            add(nv, cv, i, j);
                        }
                        if(isfree(i + 1, j)) {
                            int nv = sv(cur, j, t);
                            nv = sv(nv, j + 1, 0);
                            add(nv, cv, i, j);
                        }
                    } else {
                        int t = gv(cur, j + 1);
                        if(isfree(i, j + 1)) {
                            int nv = sv(cur, j, 0);
                            nv = sv(nv, j + 1, t);
                            add(nv, cv, i, j);
                        }
                        if(isfree(i + 1, j)) {
                            int nv = sv(cur, j, t);
                            nv = sv(nv, j + 1, 0);
                            add(nv, cv, i, j);
                        }
                    }
                }
                
            }
        }
    }
    cout << ans << "\n";
    cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
