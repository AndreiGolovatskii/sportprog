#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef vector<bool> bits;

template<const int end>
void getBuckets(int *s, int *bkt, int n, int K) {
	fill(bkt, bkt + K + 1, 0);
	forn(i, n) bkt[s[i] + !end]++;
	forn(i, K) bkt[i + 1] += bkt[i];
}
void induceSAl(bits &t, int *SA, int *s, int *bkt, int n, int K) {
	getBuckets<0>(s, bkt, n, K); 
	forn(i, n) {
		int j = SA[i] - 1;
		if (j >= 0 && !t[j])
			SA[bkt[s[j]]++] = j;
	}
}
void induceSAs(bits &t, int *SA, int *s, int *bkt, int n, int K) {
	getBuckets<1>(s, bkt, n, K);
	for (int i = n - 1; i >= 0; i--) {
		int j = SA[i] - 1;
		if (j >= 0 && t[j])
			SA[--bkt[s[j]]] = j;
	}
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n-1]=0, n>=2
void SA_IS(int *s, int *SA, int n, int K) {
	#define isLMS(i) (i && t[i] && !t[i-1])
	int i, j;
	bits t(n);
	t[n-1] = 1; 
	for (i = n - 3; i >= 0; i--)
		t[i] = (s[i]<s[i+1] || (s[i]==s[i+1] && t[i+1]==1));
	int bkt[K + 1];
	getBuckets<1>(s, bkt, n, K);
	fill(SA, SA + n, -1);
	forn(i, n)
		if (isLMS(i))
			SA[--bkt[s[i]]] = i;
	induceSAl(t, SA, s, bkt, n, K);
	induceSAs(t, SA, s, bkt, n, K);
	int n1 = 0;
	forn(i, n)
		if (isLMS(SA[i]))
			SA[n1++] = SA[i];
	fill(SA + n1, SA + n, -1);
	int name = 0, prev = -1;
	forn(i, n1) {
		int pos = SA[i];
		bool diff = false;
		for (int d = 0; d < n; d++)
			if (prev == -1 || s[pos+d] != s[prev+d] || t[pos+d] != t[prev+d])
				diff = true, d = n;
			else if (d > 0 && (isLMS(pos+d) || isLMS(prev+d)))
				d = n;
		if (diff)
			name++, prev = pos;
		SA[n1 + (pos >> 1)] = name - 1;
	}
	for (i = n - 1, j = n - 1; i >= n1; i--)
		if (SA[i] >= 0)
			SA[j--] = SA[i];
	int *s1 = SA + n - n1;
	if (name < n1)
		SA_IS(s1, SA, n1, name - 1);
	else
		forn(i, n1)
			SA[s1[i]] = i;
	getBuckets<1>(s, bkt, n, K);
	for (i = 1, j = 0; i < n; i++)
		if (isLMS(i))
			s1[j++] = i;
	forn(i, n1)
		SA[i] = s1[SA[i]];
	fill(SA + n1, SA + n, -1);
	for (i = n1 - 1; i >= 0; i--) {
		j = SA[i], SA[i] = -1;
		SA[--bkt[s[j]]] = j;
	}
	induceSAl(t, SA, s, bkt, n, K);
	induceSAs(t, SA, s, bkt, n, K);
}

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
const int N = 4e5;
char s[N + 1];
int main() {
    gets(s);
	int n = strlen(s), a[n + 1], b[n + 1];
	forn(i, n + 1)
	  b[i] = s[i];
	SA_IS(b, a, n + 1, 256);
	forn(i, n)
		printf("%d ", a[i + 1] + 1);
}
