/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

typedef long long ll;

const int maxt = 1 << 17;

int n, k;
ll t[maxt * 2];

int main() {
	n = readInt();
	k = readInt();
	assert(n <= maxt);
	while (k--) {
		char ch = readChar();
		int a = readInt(), b = readInt();
		if (ch == 'A') {
			t[--a += maxt] = b;
			for (a >>= 1; a > 1; a >>= 1)
				t[a] = t[2 * a] + t[2 * a + 1];
		} else {
			ll sum = 0;
			for (--a += maxt, --b += maxt; a <= b; a >>= 1, b >>= 1) {
				if ((a & 1))  sum += t[a++];
				if (!(b & 1)) sum += t[b--];
			}
			writeInt(sum, '\n');
		}
	}
}
