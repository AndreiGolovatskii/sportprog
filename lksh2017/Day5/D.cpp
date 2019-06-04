#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

int main() {
    ifstream cin("brackets.in");
    ofstream cout("brackets.out");

    char a;
    string str;
    while (cin >> a) {
        str.push_back(a);
    }
    int n = str.size();

    int bal = 0;
    vector<int> pref_o(1, 0);
    vector<int> pref_c(1, 0);
    for (auto i = str.begin(); i < str.end(); ++i) {
        if (*i == ')' && bal == 0) {
            pref_c.push_back(*pref_c.rbegin() + 1);
        } else if (*i == ')' && bal > 0) {
            bal--;
            pref_c.push_back(*pref_c.rbegin());
        } else {
            bal++;
            pref_c.push_back(*pref_c.rbegin());
        }
        pref_o.push_back(bal);
    }

    bal = 0;
    vector<int> suf_o(1, 0);
    vector<int> suf_c(1, 0);
    for (auto i = str.rbegin(); i < str.rend(); ++i) {
        if (*i == '(' && bal == 0) {
            suf_o.push_back(*suf_o.rbegin() + 1);
        } else if (*i == '(' && bal > 0) {
            bal--;
            suf_o.push_back(*suf_o.rbegin());
        } else {
            bal++;
            suf_o.push_back(*suf_o.rbegin());
        }
        suf_c.push_back(bal);
    }

    reverse(suf_c.begin(), suf_c.end());
    reverse(suf_o.begin(), suf_o.end());

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (pref_o[i] == 0 && suf_c[i] == 0 && pref_c[i] == suf_o[i]) {
            ans++;
        }
    }

    cout << ans;
}
