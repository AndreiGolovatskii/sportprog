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


int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    mt19937 rnd(clock());

    int n = 1e5;
    for(int i = 0; i < n; ++i)
        cout << rnd() % 10;
    cout << '\n';
    for(int i = 0; i < n; ++i)
        cout << rnd() % 10;
    cout << '\n';
    // int l = rnd() % 1000000 + 1;
    // int r = rnd() % 1000000 + 1;
    // if(l > r) swap(l, r);
    // cout << l << "\n" << r << "\n";
}
