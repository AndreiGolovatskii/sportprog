/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int n, a, b, c, m;
long long cnt = 0, sum_cnt;

int go( int dep, int i, int x ) {
	if (dep == n) {
		cnt++;
		return (i * (((long long)i * a + b) % m) + c) % m >= x;
	}
	int i0 = i, i1 = i + (1 << (n - dep - 1));
	// if (rand() & 1) swap(i0, i1); // input data is already shuffled by the statament
	int f0 = go(dep + 1, i0, x);
	return (dep & 1) == (f0 == 0) ? f0 : go(dep + 1, i1, x);
}

int main() {
	cin >> n >> a >> b >> c >> m;
	int l = 0, r = m; // the first player (he maximizes) can get l, but not r
	while (r - l > 1) {
		int x = (l + r) / 2;
		cnt = 0;
		(go(0, 0, x) ? l : r) = x;
		fprintf(stderr, "cnt = %lld of %lld (%g)\n", cnt, 1LL << n, 1. * cnt / (1LL << n));
		sum_cnt += cnt;
	}
	cout << l << endl;
	fprintf(stderr, "summary = %lld of %lld (%g)\n", sum_cnt, 1LL << n, 1. * sum_cnt / (1LL << n));
}
