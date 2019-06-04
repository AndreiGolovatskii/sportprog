/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 2e5;

struct Node {
	Node *l, *r;
};

Node* build( int n ) {
	if (n == 1)
		return new Node{0, 0};
	return new Node{build((n + 1) / 2), build(n / 2)};
}
Node* change( Node *v, int vl, int vr, int i, size_t x ) {
	if (vr - vl == 1)
		return new Node{(Node *)x, 0};
	int vm = (vl + vr + 1) / 2;
	if (i < vm)
		return new Node{change(v->l, vl, vm, i, x), v->r};
	else
		return new Node{v->l, change(v->r, vm, vr, i, x)};
}

struct PArray {
	Node *root;
	int get( int i ) {
		Node *v = root;
		for (int vm, vl = 0, vr = N; vr - vl > 1; ) 
			if (i < (vm = (vl + vr + 1) / 2))
				v = v->l, vr = vm;
			else
				v = v->r, vl = vm;
		return (size_t)v->l;
	}
	PArray set( int i, size_t x ) {
		return {change(root, 0, N, i, x)};
	}
};

struct PQueue {
	int st, en;
	PArray q;
	pair<int, PQueue> pop() {
		return {q.get(st), {st + 1, en, q}};
	}
	PQueue push( int x ) {
		return {st, en + 1, q.set(en, x)};
	}
};

int main() {
	int n = readInt();
	vector<PQueue> q;
	q.reserve(n + 1);
	q.push_back({0, 0, {build(N)}});
	while (n--) {
		int type = readInt(), i = readInt();
		if (type == -1) {
			auto pop = q[i].pop();
			q.push_back(pop.second);
			writeInt(pop.first, '\n');
		} else {
			q.push_back(q[i].push(readInt()));
		}
	}
}
