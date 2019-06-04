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

const int MN = 1e5;
int c[MN];


int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    mt19937 rnd(clock());
    
    
    int n = 1e6;
    cout << n << " " << n << "\n";
    for(int i = 0; i < n; ++i) {
        cout << i + 1 << " " << ((i + 1) % n) + 1 << "\n"; 
    }
}
