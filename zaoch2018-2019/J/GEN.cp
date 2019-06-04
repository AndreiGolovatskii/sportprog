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

    int n = 2e5, m = 2e5, q = 5e5;
    int k = (rnd() % 26) + 1;
    for (int i = 0; i < n; ++i)
    {
        cout << (char)(rnd() % k + 'a');
    }
    cout << '\n';

    for (int i = 0; i < m; ++i)
    {
        cout << (char)(rnd() % k + 'a');
    }
    cout << '\n'
         << q << '\n';
    for (int i = 0; i < q; ++i)
    {
        int l1 = rnd() % n;
        int r1 = rnd() % n;
        if (l1 > r1)
            swap(l1, r1);

        int l2 = rnd() % m;
        int r2 = rnd() % m;
        if (l2 > r2)
            swap(l2, r2);
        cout << l1 + 1 << " " << r1 + 1 << " " << l2 + 1 << " " << r2 + 1 << "\n";
    }
}
