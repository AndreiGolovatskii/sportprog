/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sz(a) (int)(a).size()
#define pb push_back

mt19937 R(239);

struct tree {
	static tree *nodeNull;
	tree *l, *r, *p;
	int x, y, size, rev;

	tree() {
		l = r = p = this;
		size = rev = 0;
	}
	tree( int x ) : x(x), y(R()), size(1), rev(0) {
		l = r = p = nodeNull;
	}
};
tree *tree::nodeNull = new tree();

const int maxN = 1e5 + 1;

int n, m, p[maxN];
tree* t[maxN];

void Calc( tree* t ) {
	if (t != tree::nodeNull)
		t->size = 1 + t->l->size + t->r->size;
}

void Down( tree* t ) {
	if (!t->rev)
		return;
	t->rev = 0;
	swap(t->l, t->r);
	t->l->rev ^= 1;
	t->r->rev ^= 1;
}

void Split( tree* t, tree* &l, tree* &r, int k ) { // size(l) = k
	if (t == tree::nodeNull) {
		l = r = tree::nodeNull;
		return;
	}
	Down(t);
	if (t->l->size + 1 <= k) 
		Split(t->r, t->r, r, k - (t->l->size + 1)), t->r->p = t, Calc(l = t);
	else 
		Split(t->l, l, t->l, k), t->l->p = t, Calc(r = t);
}

void Merge( tree* &t, tree* l, tree* r ) {
	if (l == tree::nodeNull)
		t = r;
	else if (r == tree::nodeNull)
		t = l;
	else if (l->y < r->y) 
		Down(l), Merge(l->r, l->r, r), l->r->p = l, Calc(t = l);
	else 
		Down(r), Merge(r->l, l, r->l), r->l->p = r, Calc(t = r);
}

pair<int, tree*> GetPos( tree* t ) { 
	int sum = t->l->size;
	tree *prev = t;
	while (t != tree::nodeNull) {
		if (t->rev)
			sum = t->size - sum - 1;
		prev = t, t = t->p;
		if (prev == t->r)
			sum += t->l->size + 1;
	}
	return {sum, prev};
}

tree *cutDownRoot;
tree* CutDown( int v ) {
	tree *l, *r;
	auto Pair = GetPos(t[v]);
	int pos = Pair.first;
	cutDownRoot = Pair.second;
	int next = p[cutDownRoot->x];
	if (pos + 1 == cutDownRoot->size)
		return cutDownRoot;
	Split(cutDownRoot, l, r, pos + 1);
	r->p = tree::nodeNull; // l->p will be set after
	p[r->x] = t[v]->x;
	p[l->x] = next;
	return l;
}

tree* Expose( int v, bool rev = 0 ) {
	tree* res = tree::nodeNull, *root;
	for (; v != -1; v = p[root->x]) 
		Merge(res, root = CutDown(v), res);
	res->p = tree::nodeNull;
	res->rev ^= rev;
	p[res->x] = -1;
	return res;
}

void Link( int a, int b ) {
	p[Expose(a, 1)->x] = b;
}

void Cut( int a, int b ) {
	Expose(a, 1);
	tree *l, *r, *root = Expose(b);
	Split(root, l, r, 1);
	l->p = r->p = tree::nodeNull;
	p[r->x] = p[l->x] = -1;
}

int main() {
	n = readInt();
	m = readInt();
	forn(i, n)
		t[i] = new tree(i), p[i] = -1;
	char com[8];
	while (m--) {
		readWord(com);
		int a = readInt() - 1;
		int b = readInt() - 1;
		if (!strcmp(com, "get")) {
			tree *roota = Expose(a);
			Expose(b);
			putchar(roota != cutDownRoot ? '0' : '1');
		} else if (!strcmp(com, "link")) {
			Link(a, b);
		} else { // cut
			Cut(a, b);
		}
	}
}
