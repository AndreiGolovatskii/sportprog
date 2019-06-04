/** OK, 0.233 sec, 13 mb */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define count count123

int nx[200000][26];
int m = 1, last = 0, count = 0;
int l[200000], f[200000];
char s[110000];

void addc(int x) {
	int ns = m++;
	l[ns] = ++count;
	int p = last;
	while (p != -1 && nx[p][x] == 0)
		nx[p][x] = ns, p = f[p];
	if (p == -1)
		f[ns] = 0;
	else {
		int q = nx[p][x];
		if (l[q] == l[p] + 1)
			f[ns] = q;
		else {
			int r = m++;
			memcpy(nx[r], nx[q], sizeof(nx[0]));
			f[r] = f[q], f[q] = f[ns] = r, l[r] = l[p] + 1;
			while (p != -1 && nx[p][x] == q)
				nx[p][x] = r, p = f[p];
		}
	}
	last = ns;
}

int main() {
	memset(f, -1, sizeof(f));
	while (!isEof()) {
		readLine(s);
		int n = strlen(s);
		if (s[0] == 'A') for (int i = 2; i < n; i++)
			addc(tolower(s[i]) - 'a');
		else {
			int cs = 0;
			bool ok = true;
			for (int i = 2; i < n; i++)	
				if (!(cs = nx[cs][tolower(s[i]) - 'a'])) {
					ok = false;
					break;
				}
			puts(ok ? "YES" : "NO");
		}
	}
}
