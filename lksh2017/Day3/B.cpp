#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;


int main() {
    ofstream cout("merge.out");
    ifstream cin("merge.in");
    int n;
    vector<pair<int, int>> V;
    vector<pair<int, int>> Ans;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        V.push_back({l, 0});
        V.push_back({r, 1});
    }

    sort(V.begin(), V.end());

    int count = 0;
    int start;
    for (auto i : V) {
        if (!i.second && count == 0)
            start = i.first;
        if (i.second)
            count--;
        else
            count++;
        if (count == 0)
            Ans.push_back({start, i.first});
    }

    cout << Ans.size() << "\n";
    for (auto i : Ans) {
        cout << i.first<<" " << i.second << "\n";
    }
}
