#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <tuple>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> S;
    vector<int> ans(n, 0);

    for (int i = 0; i < n; ++i) {
        int s, t;
        cin >> s >> t;
        S.emplace_back(s, 0, i);
        S.emplace_back(t, 1, i);
    }

    sort(S.begin(), S.end());

    int cnt_c = 0, cnt_o = 0;
    for (auto i : S) {
        if (get<1>(i) == 0) {
            ans[get<2>(i)] += cnt_c;
            cnt_o++;
        }
        else {
            ans[get<2>(i)] += n - cnt_o;
            cnt_c++;
        }
    }
    for (auto i : ans)
        cout << n - 1 - i << "\n";
}
