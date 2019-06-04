#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    int n, q;
    cin >> n;
    vector <pair <int, int> > Arr(n);
    for (int i=0;  i < n; ++i) {
        int c;
        cin >> c;
        Arr[i]=make_pair(c, i + 1);
    }
    sort(Arr.begin(), Arr.end());
    cin >> q;
    for (int i=0; i < q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        auto it_l = lower_bound(Arr.begin(), Arr.end(), make_pair(x, l));
        auto it_u = upper_bound(Arr.begin(), Arr.end(), make_pair(x, r));
        if (it_l == it_u)
            cout << 0;
        else
            cout << 1;
    }
}
