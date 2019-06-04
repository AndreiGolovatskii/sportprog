/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.03.31
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 100, inf = 1e9;

int n, a[N][N];
int str[N + 1], col[N + 1];
int u[N + 1], d[N + 1], la[N + 1], pa[N + 1];

void Hungrian() {
	fill(pa, pa + n + 1, -1);
	forn(k, n) {
		fill(u, u + n + 1, 0);
		fill(d, d + n + 1, inf);
		pa[n] = k;
		int l = n, x;
		while ((x = pa[l]) != -1) {
			u[l] = 1;
			#define F(v, i) (a[v][i] + str[v] + col[i])
			int mi = inf, tmp, l0 = l;
			forn(j, n)
				if (!u[j]) {
					if ((tmp = F(x, j)) < d[j])
						d[j] = tmp, la[j] = l0;
					if (d[j] < mi)
						mi = d[j], l = j;
				}
			forn(j, n + 1)
				if (u[j])
					col[j] += mi, str[pa[j]] -= mi;
				else
					d[j] -= mi;
		}
		while (l != n)
			pa[l] = pa[la[l]], l = la[l];
	}
}

int main() {
	#define NAME "credit"
	assert(freopen(NAME ".in", "r", stdin));
	assert(freopen(NAME ".out", "w", stdout));

	scanf("%d", &n);
	forn(i, n)
		forn(j, n)
			scanf("%d", &a[i][j]), a[i][j] = -a[i][j];
	Hungrian();

	forn(i, n)
		printf("%d%c", str[i], " \n"[i == n - 1]);
	forn(i, n)
		printf("%d%c", col[i], " \n"[i == n - 1]);
	return 0;
}
