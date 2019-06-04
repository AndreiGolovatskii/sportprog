#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

bool is_open(char a) {
    return (a == '(' || a == '[' || a == '{');
}


int main() {
    ofstream cout("check.out");
    ifstream cin("check.in");
    stack<char> s;
    map<char, char> pair;
    pair[')'] = '(';
    pair[']'] = '[';
    pair['}'] = '{';
    char a;
    while (cin >> a) {
        if (is_open(a))
            s.push(a);
        else {
            if (s.size() == 0 || pair[a] != s.top()) {
                cout << "NO";
                return 0;
            }
            else
               s.pop();
        }
    }
    if (s.size() == 0) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
}
