// God & me
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 17, sq = 3e2 + 17;

int n, t[maxn], q, k, l[maxn], r[maxn], per[maxn];
ll a[maxn], ans, res[maxn];
unordered_map<ll, int> cnt;
unordered_map<ll, int> :: iterator it[maxn][3];
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cnt.reserve(1 << 16);
	cin >> n >> k;
	for(int i = 0; i < n; i++)
		cin >> t[i];
	for(int i = 0; i < n; i++){
		cin >> a[i + 1];
		a[i + 1] *= t[i] * -2 + 3;
		a[i + 1] += a[i];
	}
	for(int i = 0; i <= n; i++)
		cnt[ a[i] ] = cnt[ a[i] + k ] = cnt[ a[i] - k ] = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j < 3; j++)
			it[i][j] = cnt.find(a[i] + (j - 1) * k);
	cin >> q;
	for(int i = 0; i < q; i++){
		cin >> l[i] >> r[i];
		l[i]--;
		r[i]++;
	}
	iota(per, per + q, 0);
	sort(per, per + q, [](int i, int j){
			return l[i] / sq == l[j] / sq ? (l[i] / sq) & 1 ? r[i] < r[j] : r[i] > r[j] : l[i] < l[j];
		});
	for(int i = 0, pl = 0, pr = 0; i < q; i++){
		int id = per[i], ql = l[id], qr = r[id];
		while(pl > ql){
			pl--;
			ans += it[pl][2] -> second;
			it[pl][1] -> second++;
		}
		while(pr < qr){
			ans += it[pr][0] -> second;
			it[pr][1] -> second++;
			pr++;
		}
		while(pr > qr){
			pr--;
			it[pr][1] -> second--;
			ans -= it[pr][0] -> second;
		}
		while(pl < ql){
			it[pl][1] -> second --;
			ans -= it[pl][2] -> second;
			pl++;
		}
		res[id] = ans;
	}
	for(int i = 0; i < q; i++)
		cout << res[i] << ' ';
	cout << '\n';
	return 0;
}
