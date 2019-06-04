#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int x1, x2, y1, y2;
    int x3, x4, y3, y4;
    cin >> x3 >> y3 >> x4 >> y4;
    for (int i = 1; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        x3 = max(x3, x1);
        x4 = min(x4, x2);
        y3 = max(y3, y1);
        y4 = min(y4, y2);
    }
    if (y3 > y4 || x3 > x4){
        cout << -1;
        return 0;
    }
    cout << x3 <<" " << y3 << " " << x4 << " " << y4;
}
