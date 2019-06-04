/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 2e8

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

typedef pair<int, int> pii;

mt19937 R(239);

struct node;
typedef node* pnode;
struct node {
	static pnode null;

	pnode l, r, p;
	int y, size;
	node( int y, bool isNull = 0 ) : l(null), r(null), p(this), y(y), size(!isNull) { }

	void calc() { size = 1 + l->size + r->size; }
};

pnode node::null = new node(0, 1);
struct Pair { pnode node; int x; };

void Split( pnode t, pnode &l, pnode &r, int k ) {
	if (t == node::null)
		l = r = node::null;
	else if (t->l->size < k)
		Split(t->r, t->r, r, k - t->l->size - 1), (l = t)->calc(), t->r->p = t;
	else
		Split(t->l, l, t->l, k), (r = t)->calc(), t->l->p = t;
}

pnode Merge( pnode &t, pnode l, pnode r ) {
	if (l == node::null)
		t = r;
	else if (r == node::null) 
		t = l;
	else if (l->y < r->y)
		Merge(l->r, l->r, r), (t = l)->calc(), l->r->p = l;
	else
		Merge(r->l, l, r->l), (t = r)->calc(), r->l->p = r;
	return t;
}

pnode Merge( pnode l, pnode r ) {
	return Merge(l, l, r);
}

void itIsRoot( pnode v ) {
	v->p = v;
}

pnode Rotate( pnode v, int k ) {
	pnode l, r;
	Split(v, l, r, k);
	return Merge(r, l);
}

Pair goUp( pnode v ) {
	int pos = v->l->size;
	while (v->p != v) 
		pos += (v->p->r == v ? v->p->l->size + 1 : 0), v = v->p;
	return {v, pos};
}

vector<unordered_map<int, pnode>> edges;

pnode delFirst( pnode v ) {
	pnode tmp;
	Split(v, tmp, v, 1);
	return v;
}

void cut( int i, int j ) {
	Pair pi = goUp(edges[i][j]);
	Pair pj = goUp(edges[j][i]);
	edges[i].erase(j);
	edges[j].erase(i);
	int l = min(pi.x, pj.x), r = max(pi.x, pj.x);
	pnode a, b, c;
	Split(pi.node, a, b, l); 
	Split(b, b, c, r - l);
	itIsRoot(delFirst(b));
	itIsRoot(Merge(a, delFirst(c)));
}

Pair getRoot( int v ) {
	return !edges[v].size() ? Pair{node::null, 0} : goUp(edges[v].begin()->second);
}

pnode makeRoot( int v ) {
	Pair p = getRoot(v);
	return Rotate(p.node, p.x);
}

pnode create( int a, int b ) {
	return edges[a][b] = new node(R());
}

void link( int a, int b ) {
	pnode A = makeRoot(a), B = makeRoot(b);
	itIsRoot(Merge(Merge(Merge(A, create(a, b)), B), create(b, a)));
}

int main() {
	edges.resize(readInt() + 1);
	int m = readInt();
	srand(239);
	while (m--) {
		char com[9];
		readWord(com);
		int a = readInt() - 1;
		int b = readInt() - 1;
		if (com[0] == 'g') {
			pnode va = getRoot(a).node, vb = getRoot(b).node;
			writeInt(va == vb && (va != node::null || a == b));
		} else if (com[0] == 'l')
			link(a, b);
		else 
			cut(a, b);
	}
}
