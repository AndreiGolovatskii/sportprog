/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef double dbl;
typedef long long ll;

const int maxlog = 18;
const int maxn = 1 << maxlog;
const int blen = 2;
const int base = 1e2;

struct num {
	dbl x, y;
	num() { }
	num( dbl a ) : x(cos(a)), y(sin(a)) { }
	num( dbl x, dbl y ) : x(x), y(y) { }
	num operator + ( const num &a ) const { return num(x + a.x, y + a.y); }
	num operator - ( const num &a ) const { return num(x - a.x, y - a.y); }
	num operator * ( const num &a ) const { return num(x * a.x - y * a.y, x * a.y + y * a.x); }
};

char s[maxn * blen + 1];

void read( num *a ) {
	readWord(s);
	for (int j = 0, x = 1, i = strlen(s) - 1; i >= 0; i--) {
		a[j].x += (s[i] - '0') * x, x *= 10;
		if (x == base) j++, x = 1;
	}
}

num a[maxn], b[maxn], fa[maxn], fb[maxn];
int rev[maxn];
ll res[maxn];

void fft( num *a, num *res ) {
	forn(i, maxn)
		res[rev[i]] = a[i];
	for (int k = 1; k < maxn; k *= 2) {
		num x(1, 0), root(M_PI / k);
		forn(i, maxn)
			a[i] = res[i & ~k] + res[i | k] * x, x = x * root;
		copy(a, a + maxn, res);
	}
}

void out( ll *a ) {
	int i = maxn - 1;
	while (i && !a[i])
		i--;
	writeInt((int)a[i--]);
	while (i >= 0)
		writeInt((int)a[i--], blen);
}

void timeS( const char *s = 0 ) { fprintf(stderr, "time = %.2f : %s\n", 1. * clock() / CLOCKS_PER_SEC, s ? s : ""); }

int main() {
	forn(i, maxn)
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (maxlog - 1));
	read(a);
	read(b);
	timeS("precalc");

	fft(a, fa);
	fft(b, fb);
	forn(i, maxn)
		a[i] = fa[i] * fb[i];
	fft(a, b);
	reverse(b + 1, b + maxn);
	forn(i, maxn)
		if ((res[i] += (ll)(b[i].x / maxn + 0.5)) >= base)
			res[i + 1] += res[i] / base, res[i] %= base;

	timeS("fft is done");
	out(res);
	timeS("exit");
}
