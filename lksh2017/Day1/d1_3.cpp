#include <iostream>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    ofstream cout("ejudge.out");
    ifstream cin("ejudge.in");
    int n;
    cin >> n;
    set<vector<int> > Ans;
    for (int i = 1; i <= n; ++i) {
        int s, t;
        cin >> s >> t;
        vector<int> A(3);
        A[0] = 1000 - s;
        A[1] = t;
        A[2] = i;
        Ans.insert(A);
    }

    for (auto el : Ans) {
        cout << el[2] << " ";
    }
}
