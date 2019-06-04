#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <algorithm>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define prev prev123

const int maxn = (int)1e5 + 10;

struct tree
{
  tree *l, *r, *p;
  int v, y, size, inv;
};

tree *t[maxn], mem[maxn + 1];
tree *tNull = mem + maxn;
int prev[maxn];

inline void MakeInv( tree *t )
{
  if (!t->inv)
    return;
  swap(t->l, t->r);
  t->inv = 0;
  t->l->inv ^= 1;
  t->r->inv ^= 1;
}

inline void Calc( tree *t )
{
  if (t == tNull)
    return;
  t->size = 1 + t->l->size + t->r->size;
  t->l->p = t->r->p = t;
}

tree *GetRoot( tree *t )
{
  while (t->p != tNull)
    t = t->p;
  return t;
}

tree *GetRoot( int v )
{
  return GetRoot(t[v]);
}

tree *tmp[maxn];
int len;

int GetX( tree *t )
{
  tree *t0 = t;
  len = 0;
  while (t != tNull)
    tmp[len++] = t, t = t->p;
  for (int i = len - 1; i >= 0; i--)
    MakeInv(tmp[i]);

  tree *t1;
  int sum = t0->l->size;
  while ((t1 = t0->p) != tNull)
  {
    if (t0 == t1->r)
      sum += t1->l->size + 1;
    t0 = t1;
  }
  return sum;
}

void Split( tree *t, tree* &l, tree* &r, int k )
{
  MakeInv(t);
  if (t == tNull)
    l = r = tNull;
  else if (t->l->size < k)
    l = t, Split(t->r, t->r, r, k - t->l->size - 1);
  else
    r = t, Split(t->l, l, t->l, k);
  Calc(l), Calc(r);
  l->p = r->p = tNull;
}

void Merge( tree* &t, tree *l, tree *r )
{
  MakeInv(l), MakeInv(r);
  if (l == tNull)
    t = r;
  else if (r == tNull)
    t = l;
  else if (l->y < r->y)
    t = l, Merge(t->r, t->r, r);
  else
    t = r, Merge(t->l, l, t->l);
  t->p = tNull;        
  Calc(t);
}
                
void Expose( int v )
{
  tree *root = GetRoot(t[v]), *proot;
  int p;
  while ((p = prev[root->v]) != -1) 
  {
    proot = GetRoot(t[p]);
    int Prev = prev[proot->v];

    tree *l, *r, *newT;
    Split(proot, l, r, GetX(t[p]) + 1);
    prev[r->v] = p;
    Merge(newT, l, root);
    root = newT;
    prev[root->v] = Prev;
  }
}

void MakeRoot( int v )
{
  tree *l, *r;
  Expose(v);
  Split(GetRoot(t[v]), l, r, GetX(t[v]));
  prev[l->v] = v, l->inv ^= 1;
  prev[r->v] = -1;
}

void Cut( int a, int b )
{
  tree *ta, *tb;
  if ((ta = GetRoot(a)) == (tb = GetRoot(b)))
  {
    int Prev = prev[ta->v];
    if (GetX(t[a]) < GetX(t[b])) // a ---> b
      swap(a, b);
    tree *l, *r;
    Split(ta, l, r, GetX(t[b]) + 1);
    prev[r->v] = -1, prev[l->v] = Prev;
  }
  else
    prev[prev[ta->v] == b ? ta->v : tb->v] = -1;
}

void Link( int a, int b )
{
  MakeRoot(b), prev[GetRoot(b)->v] = a;
}

int Get( int a, int b )
{
  MakeRoot(a), Expose(b);
  return GetRoot(a) == GetRoot(b) ? GetX(t[b]) : -1;
}

int main()
{
  // assert(freopen("linkcut.in", "r", stdin));
  // assert(freopen("linkcut.out", "w", stdout));

  tNull->v = maxn - 1;
  tNull->size = 0;
  tNull->l = tNull->r = tNull->p = tNull;

  forn(i, maxn)
  {
    t[i] = mem + i, prev[i] = -1;
    t[i]->l = t[i]->r = t[i]->p = tNull;
    t[i]->v = i, t[i]->y = (rand() << 15) + rand();
    Calc(t[i]);
  }

  int n, m, a, b;
  char com[9];
  scanf("%d%d", &n, &m);
  while (m-- && scanf("%s%d%d", com, &a, &b) == 3)
  {
    if (strcmp(com, "link") == 0)
      Link(a, b);
    else if (strcmp(com, "cut") == 0)
      Cut(a, b);
    else
    {
      assert(strcmp(com, "get") == 0);
      printf("%d\n", Get(a, b));
    }
  } 
  return 0;
}
