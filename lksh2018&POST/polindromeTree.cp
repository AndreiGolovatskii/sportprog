#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <cstring>

using namespace std;
mt19937 rnd;
const int MN = 1e5 + 7, ALPH = 27;


struct node{
    int suff = 0, p = 0, pval = 0;
    int len = 0;
    int ne[ALPH];
    node (int len, int p, int pval, int suff):len(len), p(p), pval(pval), suff(suff){
        memset(ne, 0, sizeof(ne));
    };
    node(){
        memset(ne, 0, sizeof(ne));
    };
};
int tit = 1, cnt = 0;
node t[MN];
char s[MN];
int mpol, rootodd, rooteven;


int nnode(int len, int p = 0, int pval = 0, int suff = 0) {
    t[tit] = node(len, p, pval, suff);
    return tit++;
}

int getsuff(int r, int pos) {
    for(;;) {
        if(t[r].ne[s[pos]]) {
            int l = t[t[r].ne[s[pos]]].len;
            if(s[pos] == s[pos - l + 1])
                return t[r].ne[s[pos]];
        } else if(r == rootodd) {
            return rooteven;
        }
        r = t[r].suff;
    }
}

void add(int pos) {
    for(;;) {
        int l = t[mpol].len;
        int pz = pos - l - 1;
        if(pz >= 0 && s[pz] == s[pos]) {
            if(t[mpol].ne[s[pos]]) {
                mpol = t[mpol].ne[s[pos]];
            } else {
                t[mpol].ne[s[pos]] = nnode(l + 2, mpol, s[pos], getsuff(t[mpol].suff, pos));
                mpol = t[mpol].ne[s[pos]];
                cnt++;
                return;
            }
            return;
        }
        mpol = t[mpol].suff;
    }
}

void prep() {
    rootodd = nnode(-1);
    t[rootodd].suff = rootodd;
    rooteven = nnode(0, 0, 0, rootodd);
    mpol = rooteven;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //    freopen("input.txt", "r", stdin);
    
    
    prep();
    
    gets(s);
    for(int i = 0; s[i] != 0; i++) {
        s[i] -= 'a';
        add(i);
        printf("%d ", cnt);
    }
}
