#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> events;
    vector<int> ans(m, 0);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        events.emplace_back(min(a, b), -1);
        events.emplace_back(max(a, b), 1e9+1);
    }
    for (int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        events.emplace_back(a, i);
    }

    sort(events.begin(), events.end());

    int count = 0;
    for (auto i : events){
        if (i.second > -1 && i.second < 1e9+1)
            ans[i.second] = count;
        else
            if (i.second == -1)
                count++;
            else
                count--;
    }
    for (auto i : ans)
        cout << i << " ";
}
