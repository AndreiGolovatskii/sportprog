#include <bits/stdc++.h>

using namespace std;
#define uint unsigned int

const int MN = 1 << 17;
int ftree[MN + 7];

void dec(int r) {
    for(; r < MN; r |= r + 1) {
        --ftree[r];
    }
}

int find(int k) {
    int l = 0, r = MN;
    while(r - l - 1) {
        int rc = ((r - l) >> 1) + l - 1;
        int rv = ftree[rc];
        if(rv >= k) {
            r = rc + 1;
        } else {
            k -= rv;
            l = rc + 1;
        }
    }
    return l;
}


int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; ++i) {
        ftree[i] = i - (i & (i + 1)) + 1;
    }
    for(int i = n; i < MN; ++i) {
        int k = i & (i + 1);
        if(k < n) {
            ftree[i] = n - k;
        }
    }


    int cur = n;
    int last = 1;
    k--;
    for(int iter = 0; iter < n; ++iter){
        int nx = (last + k) % cur;
        if(!nx) {
            nx = cur;
        }
        int pos = find(nx);
        last = nx;
        cur--;
        dec(pos);
        printf("%d ", pos + 1);
    }
}