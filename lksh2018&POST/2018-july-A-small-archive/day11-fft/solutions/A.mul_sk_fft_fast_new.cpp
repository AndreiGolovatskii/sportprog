/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

/**
 * Way #1, double		: 1e3 = OK, 1e4 = WA 15
 * Way #1, long double	: 1e5 = OK, 1e6 = WA 13
 * Way #2, double		: 1e5 = OK, 1e6 = WA 14 --> 0.08 sec
 * Way #2, long double	: 1e5 = OK, 1e6 = WA 14
 * Way #3, double		: 1e5 = OK, 1e6 = WA 14 
 * Way #3, long double	: 1e5 = OK, 1e6 = WA 14
 */

#define WAY 2
#define PRECISE 0
const int blen = 4;

#if PRECISE
typedef long double dbl;
#define COS cosl
#define SIN sinl
#else
typedef double dbl;
#define COS cos
#define SIN sin
#endif
typedef long long ll;

const int maxlog = 19 - (int)floor(log(blen) / log(2));
const int maxn = 1 << maxlog;
const int base = exp(blen * log(10)) + 0.5;

struct num {
	dbl x, y;
	num() { }
	num( dbl a ) : x(COS(a)), y(SIN(a)) { }
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
		if (x == base)
			j++, x = 1;
	}
}

num a[maxn], b[maxn], fa[maxn], fb[maxn], root[maxn];
int rev[maxn];
ll res[maxn];

void fft( const num *a, num *res ) {
	forn(i, maxn)
		res[rev[i]] = a[i];
	for (int k = 1; k < maxn; k *= 2)
		for (int i = 0; i < maxn; i += 2 * k)
			forn(j, k) {
				num tmp = root[k + j] * res[i + j + k];
				res[i + j + k] = res[i + j] - tmp;
				res[i + j] = res[i + j] + tmp;
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
	for (int k = 1; k < maxn; k *= 2) {
		num tmp(M_PI / k);
		root[k] = {1, 0};
		for (int i = 1; i < k; i++)
#if WAY == 1
			root[k + i] = root[k + i - 1] * tmp; 
#elif WAY == 2
			root[k + i] = (i & 1) ? root[(k + i) >> 1] * tmp : root[(k + i) >> 1]; // Way #2
#else
			root[k + i] = num(M_PI / k * i); // Way #3
#endif
	}
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
