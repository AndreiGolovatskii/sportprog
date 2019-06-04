#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>


using namespace std;

int n;

void gen(int pref, int bal, string & S) {
    if (pref == 2 * n) {
        if (bal == 0)
            cout << S <<"\n";
        return;
    }
    S[pref] = '(';
    gen(pref + 1, bal + 1, S);
    if (bal > 0) {
        S[pref] = ')';
        gen(pref + 1, bal - 1, S);
    }
}


int main() {
    cin >> n;
    string S(2 * n, 0);
    gen(0, 0, S);

}
