#include <iostream>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    ofstream cout("taxi.out");
    ifstream cin("taxi.in");

    multiset <pair<int, int> > L;
    multiset <pair<int, int> > P;
    int n;
    cin >> n;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        L.insert(make_pair(c, i));
    }
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        P.insert(make_pair(c, i+1));
    }

    for (auto pers : L) {
        ans[(pers).second]=(*(--P.end())).second;
        P.erase(--P.end());
    }

    for (auto i : ans) {
        cout << i << " ";
    }
}
