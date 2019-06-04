#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int main() {
    ofstream cout("decode.out");
    ifstream cin("decode.in");
    deque<char> s;
    char a;
    while (cin >> a) {
        if (s.size() > 0 && a == s.back()) {
            s.pop_back();
        }
        else {
            s.push_back(a);
        }
    }
    while (s.size() > 0) {
        cout << s.front();
        s.pop_front();
    }
}
