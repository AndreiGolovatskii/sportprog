/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef double dbl;

struct num {
	dbl x, y;
	num() { }
	num( dbl a ) : x(cos(a)), y(sin(a)) { }
	num( dbl x, dbl y ) : x(x), y(y) { }
	num operator * ( double k ) const		{ return num(x * k, y * k); }
	num operator + ( const num &a ) const	{ return num(x + a.x, y + a.y); }
	num operator - ( const num &a ) const	{ return num(x - a.x, y - a.y); }
	num operator * ( const num &a ) const	{ return num(x * a.x - y * a.y, x * a.y + y * a.x); }
	num& operator *= ( double k )			{ x *= k; y *= k; return *this; }
	num& operator *= ( const num &a )		{ return *this = *this * a; }
	num ort() { return num(x, -y); }
};

namespace FFT {
	const int maxlog = 18;
	const int maxn = 1 << maxlog;

	typedef num Vector[maxn];
	
	int _maxn, _maxlog;
	dbl _maxn_inv;

	num root[maxn], rootCache[maxn];
	int rev[maxn];

	num tmp[maxn], fa[maxn], fb[maxn]; // temporary data

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

	void fft_inv( num *a, num *res ) {
		fft(a, res);
		reverse(res + 1, res + _maxn);
		forn(i, _maxn)
			res[i] *= _maxn_inv;
	}

	template <class T>
	void get_int( num *a, T *c ) {
		forn(i, _maxn)
			c[i] = floor(a[i].x + 0.5);
	}

	void choose( int n ) {
		_maxn = 1, _maxlog = 0;
		while (_maxn < n)
			_maxn <<= 1, _maxlog++;
		assert(_maxn <= maxn);
		_maxn_inv = (dbl)1 / _maxn;
	}

	void init( int n = maxn ) {
		choose(n);
		forn(i, _maxn)
			rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (_maxlog - 1));
		for (int k = 1; k < _maxn; k *= 2) {
			num tmp(M_PI / k);
			root[k] = {1, 0};
			for (int i = 1; i < k; i++)
				root[k + i] = (i & 1) ? root[(k + i) >> 1] * tmp : root[(k + i) >> 1]; // Way #2
		}
	}

	struct Long {
		int n, a[maxn];
		int & operator [] ( int i ) { return a[i]; }
	};

	void square( Long &a, Long &c ) {
		c.n = 2 * a.n;
		init(c.n);
		forn(i, _maxn)
			tmp[i] = {(dbl)(i < a.n ? a[i] : 0), (dbl)0};
		fft(tmp, fa);
		forn(i, _maxn)
			fa[i] *= fa[i];
		fft_inv(fa, tmp);
		get_int(tmp, c.a);
	}
}

const int N = 1e5;
char s[N + 1];
FFT::Long a, a2;

int main() {
	scanf("%s", s);
	a.n = strlen(s);
	forn(i, a.n)
		a[i] = s[i] - '0';

	FFT::square(a, a2);
	
	long long ans = 0;
	forn(i, a.n)
		if (s[i] == '1')
			ans += a2[2 * i] - 1;
	cout << ans / 2 << endl;
}
