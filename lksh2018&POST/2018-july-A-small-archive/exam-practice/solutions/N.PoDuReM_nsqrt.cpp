#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

typedef long long ll;

int solve();

int main() {
	return solve();
}

const int dd = (int)1e5 + 7;
const int C = 157;

int A[dd], L[dd];
ll ans[dd];

inline void uax(ll &a, ll b) { if (a < b) a = b; }

struct Line {
	int K;
	ll B;

	Line() {}

	Line(int _K, ll _B) { K = _K, B = _B; }

	ll operator ^ (Line I) {
		return (B - I.B) / (I.K - K) - 1;
	}
};

struct CHT {
	Line T[dd];
	ll G[dd];
	int sz, j;

	void clear() { sz = j = 0; }

	bool good(Line Q) {
		if (Q.K != T[sz - 1].K)
			return G[sz - 1] > (Q ^ T[sz - 1]);
		return Q.B > T[sz - 1].B;
	}

	void add(Line Q) {
		while (sz && good(Q))
			sz--;
		if (T[sz - 1].K != Q.K) {
			G[sz] = (sz ? (Q ^ T[sz - 1]) : -(ll)1e18);
			T[sz++] = Q;
		}
	}

	ll get(int x) {
	    if (j > sz - 1) j = sz - 1;
		while (j < sz - 1 && G[j + 1] < x) ++j;
		return 1ll * T[j].K * x + T[j].B;
	}
} J;

int SzL[dd], SzR[dd];
pair<int, int> Ql[dd], Qr[dd], Kl[dd], Kr[dd];
ll gA[dd];

int solve() {
	//(i - j) * A[i] + j * (A[j] - A[i]) = i * A[i] - 2j * A[i] + j * A[j]
	int n;
	n = readInt();
	for (int i = 0; i < n; ++i)
        A[i] = readInt();
    for (int i = 0; i < n; ++i)
        gA[i] = 1ll * (i + 1) * A[i];
	for (int i = 0; i < n; ++i)
		L[i] = i / C * C;
	int q;
	q = readInt();
	for (int i = 0; i < q; ++i) {
		int l, r;
		l = readInt() - 1, r = readInt() - 1;
		if (L[l] == L[r]) {
			J.clear();
			for (int j = l; j <= r; ++j) {
				if (J.sz) uax(ans[i], J.get(-A[j]) + gA[j]);
				J.add(Line((j + 1) << 1, gA[j]));
			}
			Kl[i] = { -1, -1 };
		} else {
			J.clear();

			int Rl = L[l] + C;
			for (int j = l; j < Rl; ++j) {
				if (J.sz) uax(ans[i], J.get(-A[j]) + gA[j]);
				J.add(Line((j + 1) << 1, gA[j]));
			}

			int Lr = L[r];
			for (int j = Lr; j <= r; ++j) {
				if (J.sz) uax(ans[i], J.get(-A[j]) + gA[j]);
				J.add(Line((j + 1) << 1, gA[j]));
			}

            SzL[Rl + 1]++;
            SzR[Lr]++;
            Kl[i] = { Rl, r };
            Kr[i] = { Lr - 1, l };
		}
	} 

	for (int i = 1; i < n; ++i)
        SzL[i] += SzL[i - 1], SzR[i] += SzR[i - 1];

    for (int i = 0; i < q; ++i) if (Kl[i].first != -1) {
        Ql[SzL[Kl[i].first]++] = { Kl[i].second, i };
        Qr[SzR[Kr[i].first]++] = { Kr[i].second, i };
    }
    for (int i = n; i > 0; --i)
        SzL[i] = SzL[i - 1], SzR[i] = SzR[i - 1];
    SzL[0] = SzR[0] = 0;

    for (int i = 0; i < n; ++i) if (SzL[i + 1] - SzL[i])
        stable_sort(Ql + SzL[i], Ql + SzL[i + 1]);
    for (int i = 0; i < n; ++i) if (SzR[i + 1] - SzR[i])
        stable_sort(Qr + SzR[i], Qr + SzR[i + 1]);

	for (int i = 0; i < n; i += C) {
		if (SzL[i + 1] - SzL[i] == 0) continue;

		J.clear();
		ll cur = 0;
		int j = SzL[i];
		for (int r = i; r < n; ++r) {
			if (J.sz) uax(cur, J.get(-A[r]) + gA[r]);
			J.add(Line((r + 1) << 1, gA[r]));
			while (j < SzL[i + 1] && Ql[j].first == r)
				uax(ans[Ql[j++].second], cur);
            if (j == SzL[i + 1]) break;
		}
	}

	//A[i] * (i + 1) + A[j] * (j + 1) - 2 * i * A[j]

	for (int i = C - 1; i < n; i += C) {
		if (SzR[i + 1] - SzR[i] == 0) continue;

		J.clear();
		ll cur = 0;
		int j = SzR[i + 1] - 1;
		for (int r = i; r >= 0; --r) {
			if (J.sz) uax(cur, J.get(-r - 1) + gA[r]);
			J.add(Line(A[r] << 1, gA[r]));
			while (j >= SzR[i] && Qr[j].first == r)
				uax(ans[Qr[j--].second], cur);
            if (j < SzR[i]) break;
		}
	}

	for (int i = 0; i < q; ++i)
        writeInt(ans[i], ' ');
}
