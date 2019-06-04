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


using namespace std;
#define x first
#define y second
#define char unsigned char
#define pic pair<int, char>
const int ALPH = UCHAR_MAX + 1;

struct node{
    int suff, p;
    char pv;
    int8_t term;
    node(){};
    node(int p, char pv, int suff):p(p), pv(pv), suff(suff) {
        term = -1;
    }
};
map<pic, int> ne;
const int BSIZE = 103000;
int bit = 1, root;
node b[BSIZE];
int nnode(int p, int pv, int suff) {
    b[bit] = node(p, pv, suff);
    assert(bit < BSIZE);
    return bit++;
}
void init(){
    bit = 1;
    int fakeroot = nnode(0, 0, 0);
    root = nnode(0, 0, fakeroot);
    b[root].term = 0;
    b[fakeroot].term = 0;
    for(int i = 0; i < ALPH; ++i) {
        ne[{fakeroot, i}] = root;
    }
}

void addword(vector<char> &s) {
    int cu = root;
    for(int i = 0; i < s.size(); ++i) {
        if(ne.find({cu, s[i]}) != ne.end()) {
            cu = ne[{cu, s[i]}];
        } else {
            cu = ne[{cu, s[i]}] = nnode(cu, s[i], 0);
        }
        if(i == (int)s.size() - 1) {
            b[cu].term = 1;
        }
    }
}

int getsufflink(int r) {
    if(b[r].suff) return b[r].suff;
    int pr = b[r].p;
    int fr = b[r].pv;
    for(;;) {
        pr = getsufflink(pr);
        if(ne.find({pr, fr}) != ne.end()) {
            return b[r].suff = ne[{pr, fr}];
        }
    }
}
int gettermvert(int r) {
    if(b[r].term != -1) {
        return b[r].term;
    } else {
        return b[r].term = gettermvert(getsufflink(r));
    }
}
int checkword(vector<char> &t) {
    int cu = root;
    int res = 0;
    for(int i = 0; i < t.size(); ++i) {
        while(ne.find({cu, t[i]}) == ne.end()) {
            cu = getsufflink(cu);
        }
        cu = ne[{cu, t[i]}];
        if(gettermvert(cu)) {
            res = max(res, i + 1);
        }
    }
    return res;
}
bool proc(char a) {
    return !(a == '\n' || a == '\0' || a == '\r');
}

int main() {
    //    auto ts = clock();
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //     freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    init();
    
    int n;
    scanf("%d", &n);
    while (getchar()!='\n');
    vector<char> in, t;
    int sumsize = 0;
    for(int i = 0; i < n; ++i) {
        char c;
        while (proc(c = getchar())) {
            in.push_back(c);
        }
        reverse(in.begin(), in.end());
        addword(in);
        sumsize += in.size();
        if(sumsize > BSIZE) {
            while (true);
        }
        //        assert(sumsize < 100 * 1024 * 8);
        in.clear();
    }
    
    int m;
    scanf("%d", &m);
    while (getchar()!='\n');
    for(int i = 0; i < m; ++i) {
        char c;
        while (proc(c = getchar())) {
            t.push_back(c);
        }
        int p;
        reverse(t.begin(), t.end());
        if((p = checkword(t)) != 0) {
            printf("%d %d\n", i + 1, (int)t.size() - p + 1);
            //            cerr << "Fast :" << ((double)clock() - ts) / CLOCKS_PER_SEC << " Sec,\n";
            return 0;
        }
        t.clear();
    }
    
    printf("Passed\n");
    
    //    cerr << "Fast :" << ((double)clock() - ts) / CLOCKS_PER_SEC << " Sec,\n";
}
