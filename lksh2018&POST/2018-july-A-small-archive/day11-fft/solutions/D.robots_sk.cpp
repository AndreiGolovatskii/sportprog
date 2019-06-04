/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * FFT Calls: 5
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#define real(a) (a).x
#define imag(a) (a).y

typedef double dbl;

struct num {
	dbl x, y;
	
	num() { }
	num( dbl a ) : x(cos(a)), y(sin(a)) { }
	num( dbl x, dbl y ) : x(x), y(y) { }
	
	num operator + ( const num &a ) const { return num(x + a.x, y + a.y); }
	num operator - ( const num &a ) const { return num(x - a.x, y - a.y); }
	num operator * ( dbl k ) const { return num(x * k, y * k); }
	num operator / ( dbl k ) const { return num(x / k, y / k); }

	num& operator += ( const num &a ) { return *this = num(x + a.x, y + a.y); }
	num& operator -= ( const num &a ) { return *this = num(x - a.x, y - a.y); }
	num& operator *= ( dbl k ) { return *this = num(x * k, y * k); }
	num& operator /= ( dbl k ) { return *this = num(x / k, y / k); }

	friend num operator * ( dbl k, const num &a ) { return num(a.x * k, a.y * k); }
	friend num operator / ( dbl k, const num &a ) { return num(a.x / k, a.y / k); }

	dbl norm() const { return x * x + y * y; }
	num ort() const { return num(x, -y); }
	num inv() const { return ort() / norm(); } 

	num operator * ( const num &a ) const { return num(x * a.x - y * a.y, x * a.y + y * a.x); }
	num operator / ( const num &a ) const { return *this * a.inv(); }

	num& operator *= ( const num &a ) { return *this = num(x * a.x - y * a.y, x * a.y + y * a.x); }
	num& operator /= ( const num &a ) { return *this *= a.inv(); }
};

const int maxlog = 18;
const int maxn = 1 << maxlog;

num root[maxn];
int rev[maxn];
int _maxn = 1, _maxlog = 0;

void fft( num *a, num *res ) {
	forn(i, _maxn)
		res[rev[i]] = a[i];
	for (int k = 1; k < _maxn; k *= 2)
		for (int i = 0; i < _maxn; i += 2 * k)
			forn(j, k) {
				num tmp = root[k + j] * res[i + j + k];
				res[i + j + k] = res[i + j] - tmp;
				res[i + j] = res[i + j] + tmp;
			}
}

void init() {
	forn(i, _maxn)
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (_maxlog - 1));
	for (int k = 1; k < _maxn; k *= 2) {
		num tmp(M_PI / k);
		root[k] = {1, 0};
		for (int i = 1; i < k; i++)
			root[k + i] = (i & 1) ? root[(k + i) >> 1] * tmp : root[(k + i) >> 1]; // Way #2
	}
}

const int N = maxn / 2;

num a[maxn], fa[maxn], all[maxn];
int n, *c = (int *)fa, *sum = (int *)all;
char s[N + 1], t[N + 1];
string alpha = "ACGT";

int main() {
	n = readInt();
	readWord(s);
	readWord(t);
	while (_maxn < 2 * n)
		_maxn <<= 1, _maxlog++;

	init();
	for (auto ch : alpha) {
		memset(a, 0, sizeof(a));
		forn(i, n)
			a[i] = num(1. * (s[i] == ch), 1. * (t[n - i - 1] == ch));
		fft(a, fa);
		forn(i, _maxn) {
			num &z0 = fa[i], &z1 = i ? fa[_maxn - i] : fa[0];
			num x(real(z0) + real(z1), imag(z0) - imag(z1));
			num y(imag(z0) + imag(z1), real(z1) - real(z0));
			all[i] += x * y;
		}
	}

	fft(all, a);
	reverse(a + 1, a + _maxn);
	forn(i, 2 * n)
		c[i] = floor(real(a[i]) / _maxn / 4 + 0.5);
	forn(j, n)
		sum[j] = c[j + (n - 1)] + (j > 0 ? c[j - 1] : 0);

	int i = max_element(sum, sum + n) - sum;
	printf("%d %d\n", sum[i], i);
}
