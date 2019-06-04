/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, a, b, c, m;

int go( int dep, int i, int l, int r ) {
	if (dep == n) {
		int res = (i * (((long long)i * a + b) % m) + c) % m;
		return min(r, max(l, res));
	}
	int f0 = go(dep + 1, i, l, r), i1 = i + (1 << (n - dep - 1));
	if ((dep & 1) == 1 && f0 == l) return l; 
	if ((dep & 1) == 0 && f0 == r) return r; 
	((dep & 1) ? r : l) = f0;
	return go(dep + 1, i1, l, r);
}

int main() {
	cin >> n >> a >> b >> c >> m;
	cout << go(0, 0, 0, m - 1) << endl;
}
