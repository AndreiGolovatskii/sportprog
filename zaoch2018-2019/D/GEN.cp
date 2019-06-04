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
#include <functional>
#include <cassert>
#include <cstring>
#include <list>
#include <bitset>
#include <deque>
#include <complex>
#include <cmath>

using namespace std;
#define x first
#define y second
#define ll long long
#define ld long double

mt19937 rnd(time(0));

int ed(int m) {
    return rnd() % m;
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int n = 5e5;
    int q = 2e5, qc = 5e4;
    int K = n - 1;
    
    
    cout << n << " " << q + qc << "\n";
    for(int i = 0; i < n; ++i) {
        cout << ed(n / 15) << " ";
    }
    cout << "\n";
    
    std::vector<string> os;
    
    for(int i = 0; i < q; ++i) {
        int a = ed(n) + 1;
        int b = ed(n) + 1;
        if(a > b) swap(a, b);
        
        os.push_back("? " +  to_string(a) + " " +  to_string(b) + "\n");
    }
    
    for(int i = 0; i < qc; ++i) {
        os.push_back("! " +  to_string(ed(n) + 1) + " " +  to_string(ed(K)) + "\n");
    }
    
    shuffle(os.begin(), os.end(), rnd);
    for(auto s : os){
        cout << s;
    }
}


