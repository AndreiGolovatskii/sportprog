#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    //ofstream cout("check.out");
    //ifstream cin("check.in");
    int n, m;
    cin >> m >> n;
    bool flag = false;

    vector<bool> ox(m, false);
    vector<bool> oy(n, false);
    vector<bool> diagonal(n + m + 1, false);
    for (int x = m - 1; x >= 0; --x) {
        for (int y = n - 1; y >= 0; --y) {
            if (!(ox[x] || oy[y] || diagonal[x - y + n])) {
                flag = false;
                ox[x] = true;
                oy[y] = true;
                diagonal[x - y + n] = true;
            } else {
                flag = true;
            }
        }
    }
    if(flag)
        cout << 1;
    else
        cout << 2;
}
