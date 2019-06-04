#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for(int i = 0; i < (n); i++)

typedef long long i64;

struct cd {
	double x, y;
};

int a, b, c, d, e, f;

inline cd calc(int k) {
	return {
		((a + (i64)b * k) ^ ((i64)c * k)) * 0.001,
		((d + (i64)e * k) ^ ((i64)f * k)) * 0.001
	};
}

int main() {
	int n = readInt();
	a = readInt();
	b = readInt();
	c = readInt();
	d = readInt();
	e = readInt();
	f = readInt();
	int m = readInt();
	forn(i, m) {
		int k = readInt();
		cd z0 = calc(k);
		cd z1 = calc(k ? (n-k) : 0);
		writeDouble((z0.x + z1.x) * 0.5, 4), writeChar(' ');
		writeDouble((z0.y - z1.y) * 0.5, 4), writeChar(' ');
		writeDouble((z0.y + z1.y) * 0.5, 4), writeChar(' ');
		writeDouble(-(z0.x - z1.x) * 0.5, 4), writeChar('\n');
	}
}
