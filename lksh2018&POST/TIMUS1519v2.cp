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
const int HS = 50123;
struct hmap{
    struct node{
        node *ne;
        int key;
        ll val;
        node(){};
        node(node *ne, int key, ll val):ne(ne), key(key), val(val){};
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
string in[MN];
inline bool isfree(int x, int y) {
    return x < n && y < m && in[x][y] != '*';
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
hmap pr;

queue<state> nextQ, curQ;
void calc(int cur){
    stack<int> st;
    int curc = cur;
    for(int i = 0; i <= m; ++i) {
        int t = curc & 3;
        curc >>= 2;
        if(!t) continue;
        if(t == 1) st.push(i);
        else {
            if(st.size()) {
                pr[(cur << 4) + st.top()] = i + 1;
                pr[(cur << 4) + i] = st.top() + 1;
                st.pop();
            } else {
                pr[(cur << 4) + i] = -1;
            }
        }
    }
    while(st.size()) {
        pr[(cur << 4) + st.top()] = -1;
        st.pop();
    }
}

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
    ll &k = pr[(cur << 4) + j];
    if(!k) {
        calc(cur);
        k = pr[(cur << 4) + j];
    }
    if(k == -1) return 0;
    cur = sv(cur, k - 1, 1);
    return 1;
}

bool otoc(int &cur, int j) {
    ll &k = pr[(cur << 4) + j];
    if(!k) {
        calc(cur);
        k = pr[(cur << 4) + j];
    }
    if(k == -1) return 0;
    cur = sv(cur, k - 1, 2);
    return 1;
}

int32_t main() {
    auto ts = clock();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // freopen("input.txt", "r", stdin);
    
    cin >> n >> m;
    
    for(int i = 0; i < n; ++i) {
        cin >> in[i];
    }
    pii last = {0, 0};
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(in[i][j] != '*') {
                last = {i, j};
            }
        }
    }
    
    state start = 0;
    nextdp[start] = 1;
    
    nextQ.push(start);
    
    ll ans = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            swap(nextQ, curQ);swap(nextdp, curdp);
            while(curQ.size()) {
                state cur = curQ.front();curQ.pop();
                ll cv = curdp[cur];
                if(!isfree(i, j)) {
                    if(gv(cur, j) || gv(cur, j + 1))
                        continue;
                    else
                        add(cur, cv, i, j);
                } else {
                    if(gv(cur, j) && gv(cur, j + 1)) {
                        if(i == last.x && j == last.y)
                            ans += cv;
                        else if(gv(cur, j) == 1 && gv(cur, j + 1) == 2) {
                            continue;
                        } else if(gv(cur, j) == 2 && gv(cur, j + 1) == 1){
                            add(sv(sv(cur, j, 0), j + 1, 0), cv, i, j);
                        }else if(gv(cur, j) == 1 && gv(cur, j + 1) == 1){
                            if(ctoo(cur, j + 1))
                                add(sv(sv(cur, j, 0), j + 1, 0), cv, i, j);
                        } else {
                            if(otoc(cur, j))
                                add(sv(sv(cur, j, 0), j + 1, 0), cv, i, j);
                        }
                    } else if(!gv(cur, j) && !gv(cur, j + 1)) {
                        if(!isfree(i, j + 1)) continue;
                        if(!isfree(i + 1, j)) continue;
                        
                        add(sv(sv(cur, j, 1), j + 1, 2), cv, i, j);
                    } else {
                        int t;
                        if(gv(cur, j))
                            t = gv(cur, j);
                        else
                            t = gv(cur, j + 1);
                        if(isfree(i, j + 1))
                            add(sv(sv(cur, j, 0), j + 1, t), cv, i, j);
                        if(isfree(i + 1, j))
                            add(sv(sv(cur, j, t), j + 1, 0), cv, i, j);
                    }
                }
                
            }
        }
    cout << ans << "\n";
    cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
