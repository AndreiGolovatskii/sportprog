/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef vector<int> T;

T a, b, c;
int inv[7];

void read( T &a ) {
	int k = readInt();
	a.resize(k + 1);
	for (int &x : a) x = readInt();
	reverse(a.begin(), a.end());
}

void print( T &a ) {
	if (!a.size())
		a.push_back(0);
	while (a.size() > 1U && a.back() % 7 == 0)
		a.pop_back();
	writeInt(a.size() - 1, ' ');
	while (a.size())
		writeInt((a.back() % 7 + 7) % 7, ' '), a.pop_back();
	writeChar('\n');
}
	
int main() {
	forn(i, 7)
		forn(j, 7)
			if ((i * j) % 7 == 1)
				inv[i] = j;
				
	read(a), read(b);
	int sh = a.size() - b.size();
	while (a.size() >= b.size()) {
		const int x = ((a.back() * inv[b.back()]) % 7 + 7) % 7;
		c.push_back(x);
		forn(i, b.size()) a[sh + i] -= x * b[i];
		a.pop_back(), sh--;
	}
	reverse(c.begin(), c.end());
	print(c);
	print(a);
}
