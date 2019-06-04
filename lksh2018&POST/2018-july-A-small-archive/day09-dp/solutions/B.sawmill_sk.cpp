/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cassert>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <functional>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
	int n;
	scanf("%d", &n);
	vector<int> w(n), sw(n + 1), d(n), x(n + 1), f0(n + 1);
	forn(i, n)
		scanf("%d%d", &w[i], &d[i]);
	for (int i = n - 1; i >= 0; i--) {
		x[i] = x[i + 1] + d[i];
		sw[i] = sw[i + 1] + w[i];
		f0[i] = f0[i + 1] + w[i] * x[i];
	}
	auto F = [&]( int l, int r ) { // [l, r)
		return f0[l] - f0[r] - (sw[l] - sw[r]) * x[r];
	};

	vector<int> f = f0, f1(n + 1);
	forn(k, 2) {
		// Divide and Conquer on [l, r) [pl, pr]
		function<void(int, int, int, int)> go = [&]( int l, int r, int pl, int pr ) {
			if (l >= r)
				return;
			int m = (l + r) / 2, p = -1, opt = INT_MAX, tmp;
			for (int j = max(pl, m); j <= min(n - 1, pr); j++)
				if (opt > (tmp = f[j + 1] + F(m, j))) 
					opt = tmp, p = j;
			f1[m] = opt;
			go(l, m, pl, p);
			go(m + 1, r, p, pr);
		};
		go(0, n, 0, n - 1);
		f.swap(f1);
	}
	printf("%d\n", f[0]);
}
