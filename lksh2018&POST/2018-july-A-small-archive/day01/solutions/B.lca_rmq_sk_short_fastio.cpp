/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

const int maxn = 1e5 + 3, maxd = 18;

int n, m;
char bn[maxn * 2];
int tt, pos[maxn];
int an, av[maxn];
int f[maxd][maxn * 2];
int *a = f[0], *head = f[1], *Next = head + maxn;

inline void dfs( int v ) {
	int T = tt++;
	pos[v] = an, av[T] = v, a[an++] = T;
	for (int e = head[v]; e; e = Next[e])
		dfs(e), a[an++] = T;
}

int ans = 0;
long long sum = 0;

inline int Get( int l, int r ) {
	if (l > r)
		swap(l, r);
	int i = bn[r - l + 1];
	return min(f[i][l], f[i][r - (1 << i) + 1]);
}

inline void Solve( int v, int u ) {
	sum += (ans = av[Get(pos[v], pos[u])]);
}

int main() {
	n = readInt();
	m = readInt();
	for (int i = 1; i < n; i++)	{
		int pr = readInt();
		Next[i] = head[pr], head[pr] = i; // to[i] = i
	}
	dfs(0);

	bn[0] = -1;
	for (int i = 1; i <= an + 1; i++)
		bn[i] = bn[i >> 1] + 1;
	for (int j = 1; j < maxd; j++)
		for (int i = 0; i + (1 << j) <= an; i++)
			f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);

	int a2 = readInt();
	int a1 = readInt();
	int x = readInt();
	int y = readInt();
	int z = readInt();
	int a0;
	while (m--) {
		Solve((a2 + ans) % n, a1);
		for (int w = 0; w < 2; w++)
			a0 = (1LL * x * a2 + 1LL * y * a1 + z) % n, a2 = a1, a1 = a0;
	}
	printf("%lld\n", sum);
}
