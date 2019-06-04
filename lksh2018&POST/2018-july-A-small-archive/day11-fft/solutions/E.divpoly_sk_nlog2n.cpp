/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int LOG = 17, LEN = 1 << LOG;
const int N = 1 << (LOG - 1), MEM = N;
int mpos, mem[MEM];

int read( int *a ) {
	int k = readInt();
	forn(i, k + 1) a[k - i] = readInt();
	return k;
}
void out( int k, int *a ) {
	while (k >= 0 && !a[k])
		k--;
	k = max(k, 0);
	writeInt(k, ' ');
	while (k >= 0)
		writeInt(a[k--], ' ');
	writeChar('\n');
}
int get( int *a, int i ) { 
	return i < 0 ? 0 : a[i];
}

typedef double dbl;

struct num {
	dbl x, y;
	num() { }
	num( dbl a ) : x(cos(a)), y(sin(a)) { }
	num( dbl x, dbl y ) : x(x), y(y) { }
	num operator * ( double k ) const     { return num(x * k, y * k); }
	num operator + ( const num &a ) const { return num(x + a.x, y + a.y); }
	num operator - ( const num &a ) const { return num(x - a.x, y - a.y); }
	num operator * ( const num &a ) const { return num(x * a.x - y * a.y, x * a.y + y * a.x); }
	num ort() { return num(x, -y); }
};

int rev[LEN];
num z[LEN], fz[LEN], root[LEN];

void fft( int N, const num *a, num *res ) {
	int bits = 0;
	while ((N << bits) < LEN) bits++;
	forn(i, N)
		res[rev[i] >> bits] = a[i];
	for (int k = 1; k < N; k *= 2)
		for (int i = 0; i < N; i += 2 * k)
			forn(j, k) {
				num tmp = root[k + j] * res[i + j + k];
				res[i + j + k] = res[i + j] - tmp;
				res[i + j] = res[i + j] + tmp;
			}
}

void mul( int n, int *a, int *b, int *c ) {
	int N = 2 * n;
	if (n <= 16) {
		fill(c, c + N, 0);
		forn(i, n) forn(j, n) c[i + j] += a[i] * b[j];
		return;
	}
	forn(i, N)
		z[i] = i < n ? num(a[i], b[i]) : num(0, 0);
	fft(N, z, fz);
	forn(i, n + 1) {
		int j = i ? N - i : 0;
		num z0 = fz[i], z1 = fz[j];
		fz[i] = num(z0.x + z1.x, z0.y - z1.y) * num(z0.y + z1.y, z1.x - z0.x) * 0.25;
		fz[j] = fz[i].ort();
	}
	fft(N, fz, z);
	forn(i, N)
		c[i] = (int)(z[i ? N - i : 0].x / N + 0.5);
}

int a[N], b[N], d[N], c[2 * N], A[N], B[N], invB, inv[7];

inline void divide( int n, int *a, int *b, int *d ) {
	if (n == 1) {          
		*d = *a * inv[*b];
		return;
	}
	int n1 = n / 2, *a0 = mem + mpos; mpos += n1;
	copy(a + n1, a + n, a0);
	divide(n1, a + n1, b + n1, d + n1);
	copy(a0, a0 + n1, a + n1);
	mpos -= n1;
	mul(n, b, d, c);
	forn(i, n1) a[i] = (7000000 + a[i] - c[i + n - 1]) % 7; 
	divide(n1, a, b + n1, d);
}

void pow2( int &k ) {
	while (k & (k - 1)) k++;
}

int main() {
	inv[1] = 1;
	for (int i = 2; i < 7; i++)
		inv[i] = (7 - (7 / i) * inv[7 % i] % 7) % 7;
		
	forn(i, LEN)
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (LOG - 1));
	for (int k = 1; k < LEN; k *= 2) {
		num tmp(M_PI / k);
		root[k] = {1, 0};
		for (int i = 1; i < k; i++)
			root[k + i] = (i & 1) ? root[(k + i) >> 1] * tmp : root[(k + i) >> 1]; // Way #2
	}

	int ak = read(a), bk = read(b), k = ak - bk + 1, n = max(bk + 1, k);
	invB = inv[b[bk]];
	if (k > 0) {
		pow2(k);
		forn(i, k) A[k - i - 1] = get(a, ak - i);
		forn(i, k) B[k - i - 1] = get(b, bk - i);
		divide(k, A, B, d);
		int shift = k - (ak - bk + 1);
		forn(i, k)
			d[i] = (i + shift < k ? d[i + shift] % 7 : 0);
	}
	pow2(n);
	mul(n, d, b, c);
	forn(i, n) a[i] = (7000000 + a[i] - c[i]) % 7;
	out(ak - bk, d);
	out(bk - 1, a);
}
