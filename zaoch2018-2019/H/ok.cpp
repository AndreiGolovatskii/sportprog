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

int res(int a)
{
    int res = 1;
    while (a)
    {
        res *= a % 10;
        a /= 10;
    }
    return res;
}

int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int l, r;
    cin >> l >> r;
    int opt = l;
    for (int i = l; i < r + 1; ++i)
    {
        if (res(opt) < res(i))
        {
            opt = i;
        }
    }
    cout << opt << '\n';
}
