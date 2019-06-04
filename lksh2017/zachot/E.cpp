#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <stack>


using namespace std;

int n, k;

void gen(int pref, stack<char> bal, string & S, int &cnt) {
    if (cnt >= k)
        return;
    if (pref == 2 * n) {
        if (bal.size() == 0) {
            cout << S << "\n";
            cnt++;
        }
        return;
    }
    if (bal.size() > 0 && bal.top() == '[') {
        S[pref] = ']';
        bal.pop();
        gen(pref + 1, bal, S, cnt);
        bal.push('[');
    }
    S[pref] = '(';
    bal.push('(');
    gen(pref + 1, bal, S, cnt);
    bal.pop();

    S[pref] = '[';
    bal.push('[');
    gen(pref + 1, bal, S, cnt);
    bal.pop();
    if (bal.size() > 0 && bal.top() == '(') {
        S[pref] = ')';
        bal.pop();
        gen(pref + 1, bal, S, cnt);
        bal.push('(');
    }
}


int main() {
    cin >> n >> k;
    string S(2 * n, 0);
    stack<char> st;
    int cnt = 0;
    gen(0, st, S, cnt);
    S = "s";
}
