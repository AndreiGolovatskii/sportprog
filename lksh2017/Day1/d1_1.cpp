#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

int main() {
    ofstream cout("arrival.out");
    ifstream cin("arrival.in");
    deque<int> Ans;
    multiset<pair<int, int> > Arr;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int c;
        cin >> c;
        Arr.insert(make_pair(c, i + 1));
    }

    int ans = 0;
    while (n > 0) {
        if (!Arr.size() > 0) {
            ans = -1;
            Ans.clear();
            break;
        }
        n -= (*(--Arr.end())).first;
        Ans.push_back((*(--Arr.end())).second);
        Arr.erase(--Arr.end());
        ans++;
    }

    cout << ans << "\n";
    while (!Ans.empty()) {
        cout << Ans.front() << " ";
        Ans.pop_front();
    }
}
