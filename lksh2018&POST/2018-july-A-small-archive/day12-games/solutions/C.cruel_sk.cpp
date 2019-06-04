#include <cstdio>
#include <cstring>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 5000;

int n, f[N + 1];
int cc, was[N + 1];

int main() {
	assert(scanf("%d", &n) == 1 && n <= N);
	f[0] = f[1] = 0;
	for (int i = 2; i <= n; i++) {
		cc++;
		forn(j, i)
			was[f[j] ^ f[i - j - 1]] = cc;
		while (was[f[i]] == cc)
			f[i]++;
	}
	if (f[n]) {
		puts("Schtirlitz");
		forn(i, n)
			if (!(f[i] ^ f[n - i - 1]))
				printf("%d\n", i + 1);
	}
	else
		puts("Mueller");
}
