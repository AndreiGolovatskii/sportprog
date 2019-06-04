#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

int count(int n, vector<bool> &diag_1, vector<bool> &diag_2, vector<bool> &oy, int x) {
    if (x == n)
        return 1;
    int ans = 0;
    for (int y = 0; y < n; ++y) {
        if (oy[y] || diag_1[x + y] || diag_2[x - y + n])
            continue;
        else {
            oy[y] = true;
            diag_1 [x + y] = true;
            diag_2 [x - y + n] = true;
            ans += count(n, diag_1, diag_2, oy, x + 1);
            oy[y] = false;
            diag_1 [x + y] = false;
            diag_2 [x - y + n] = false;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<bool> diag_1(n * 2), diag_2 (n * 2), oy(n);
    cout << count(n, diag_1, diag_2, oy, 0);
}
