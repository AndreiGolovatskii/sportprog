#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

int a, b, c, d;

float f(float x) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}


int main() {
    ofstream cout("cubroot.out");
    ifstream cin("cubroot.in");
    cin >> a >> b >> c >> d;
    if (a < 0) {
        a = -a;
        b = -b;
        c = -c;
        d = -d;
    }
    float x = 1;
    while (f(x) < 0) {
        x *= 2;
    }
    float right = x;
    x = -1;
    while (f(x) > 0) {
        x *= 2;
    }
    float left = x;

    for (int i = 0; i < 1e3; ++i) {
        float mid = (left + right) / 2;
        float a = f(mid);
        float b = f(right);
        if (a > 0 && b > 0)
            right = mid;
        else
            left = mid;
    }
    cout << left;
}
