#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const int INF=1e9;
long double a1, a2, b1, b2;

long double ans(long double k) {
    long double a = 1, b = a * k;
    long double ans = hypot((a1 * a + b1 * b), (a2 * a + b2 * b)) / (hypot(a, b));
    return ans;
}

int main()
{
    cout.precision(10);
    cout << fixed;
    cin >> a1 >> b1 >> a2 >> b2;
    long double r = 100000000;
    long double l = 0;
    for (int i = 0; i < 100; ++i) {
        long double m1 = l + (r - l) / 3;
        long double m2 = r -  (r - l) / 3;

        if (ans(m1) > ans(m2)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    cout << ans(r);
    system("pause");
}

