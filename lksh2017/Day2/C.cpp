#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

int Vp, Vf;
double a;

using namespace std;

double time(double X){
    return hypot(1 - a, X) / Vp + hypot(a, 1 - X) / Vf;
}


int main() {
    ofstream cout("forest.out");
    ifstream cin("forest.in");

    cout.precision(10);
    cout << fixed;

    cin >> Vp >> Vf >> a;
    double left = 0;
    double right = 1;
    for (int i = 0; i < 100; ++i) {
        double m1 = left + (right - left) / 3;
        double m2 = right - (right - left) / 3;
        if (time(m1) < time(m2))
            right = m2;
        else
            left = m1;
    }
    cout << right;
}
