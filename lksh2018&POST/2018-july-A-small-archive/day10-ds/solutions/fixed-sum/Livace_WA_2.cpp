#include <bits/stdc++.h>
using namespace std;


#define f(_i, _n) for (auto _i = 0; _i < _n; _i++)
#define F(_i, _k, _n) for (auto _i = _k; _i < _n; _i++)
#define fr(_i, _k, _n) for (auto _i = _k; _i < _n; _i++)
#define r(_t, _n)     _t _n;     cin >> _n;
#define ra(_type, _name, _len)_type _name[_len]; f(_i, _len)    cin >> _name[_len];
#define mp make_pair
#define re return
#define takedown re 0;
#define fi first
#define se second
#ifdef FairlyLocal
 #define deb cerr
#else
 #define deb GetCE :(
#endif
#define pb push_back
#define fill(_a, _n) memset(_a, _n, sizeof(_a))
#define all(_v) _v.begin(), _v.end()
#define vi std::vector<int>
#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }
// #define abs(x) (((x) > 0) ? (x) : (-x))

template<typename A, typename B> bool mini(A &x, const B &y) {
  if (y < x) {
    x = y;
    return true;
    }
  return false;
}

template<typename A, typename B> bool maxi(A &x, const B &y) {
  if (y > x) {
    x = y;
    return true;
    }
  return false;
}

typedef pair<int,int> pii;
typedef long long ll;

#ifndef FairlyLocal
  class fastio {
  public:
   fastio() {
     ios::sync_with_stdio(false);
     cin.tie(nullptr);
   }
  } __fastio;
#endif


typedef long long ll;
typedef pair<int, int> pii;
typedef long double ld;

ll pref[300500];
map<ll, int> c;
ll val[300500];
int cnt[300500];

int t[300500];
int a[300500];

int l[300500];
int r[300500];

pair<pii, int> b[300500];

int sz = 400;

ll ans = 0;
ll res[100500];

bool cmp (const pair<pii, int> & a, const pair<pii, int> & b) {
  if (a.fi.fi / sz != b.fi.fi / sz) {
    re a.fi.fi < b.fi.fi;
  }
  if (a.fi.se != b.fi.se) re a.fi.se < b.fi.se;
  if (a.fi.fi != b.fi.fi) re a.fi.fi < b.fi.fi;
  re a.se < b.se;
}

int cur = 0;
int get(int v) {
  if (c.count(v)) re c[v];
  c[v] = cur++;
  re c[v];
}
void addl(int i) {
  ans += cnt[r[a[i]]];
  cnt[a[i]]++;
}
void addr(int i) {
  ans += cnt[l[a[i]]];
  cnt[a[i]]++;
}

void reml(int i) {
  ans -= cnt[r[a[i]]];
  cnt[a[i]]--;
}
void remr(int i) {
  ans -= cnt[l[a[i]]];
  cnt[a[i]]--;
}

int main() {
  ll n, k;
  cin >> n >> k;

  f(i, n) {
    cin >> t[i];
  }

  f(i, n) {
    cin >> a[i];
    if (t[i] == 2) a[i] = -a[i];
    pref[i + 1] = pref[i] + a[i];
  }

  f(i, n + 1) {
    a[i] = get(pref[i]);
    l[a[i]] = get(pref[i] - k);
    r[a[i]] = get(pref[i] + k);
  }

  int q;
  cin >> q;

  f(i, q) {
    cin >> b[i].fi.fi >> b[i].fi.se;
    b[i].fi.se++;
    b[i].fi.fi--;
    b[i].se = i;
  }

  sort(b, b + q, cmp);

  int lb = b[0].fi.fi;
  int rb = lb - 1;

  f(i, q) {
    while (rb < b[i].fi.se) {
      rb++;
      addr(rb);
    }
    while (lb < b[i].fi.fi) {
      reml(lb);
      lb++;
    }

    while (lb > b[i].fi.fi) {
      lb--;
      addl(lb);
    }
    while (rb > b[i].fi.se) {
      remr(rb);
      rb--;
    }
    // cerr << lb << ' ' << rb << ' ' << ans << '\n';
    res[b[i].se] = ans;
  }
  f(i, q) {
    cout << res[i] << '\n';
  }
}
