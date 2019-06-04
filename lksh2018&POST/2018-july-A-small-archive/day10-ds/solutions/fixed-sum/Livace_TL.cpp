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

ll pref[100500];
map<ll, int> c;
ll val[100500];
int cnt[100500];

int t[100500];
int a[100500];

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
  int q;
  cin >> q;
  f(_, q) {
    int l, r;
    cin >> l >> r;
    r++;
    ll ans = 0;
    for (int i = l; i < r; i++) {
      for (int j = i; j < r; j++) {
        if (pref[j] - pref[i - 1] == k) ans++;
      }
    }
    cout << ans << '\n';
  }
}
