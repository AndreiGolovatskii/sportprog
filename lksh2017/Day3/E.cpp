#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <tuple>

using namespace std;

const int H = 60 * 60;
const int M = 60;
const int D = 12 * 60 * 60;
vector<int> times;
int n;

int f(int time) {
    int sum = 0;
    for (auto i : times) {
        sum += (time - i + D) % D;
    }
    return sum;
}

int main() {
    cin >> n;
    for ( int i = 0; i < n; ++i) {
        int h, m, s;
        scanf("%d:%d:%d", &h, &m, &s);
        s += h * H + m * M;
        times.push_back(s);
    }

    sort(times.begin(), times.end());

    int min = f(times[0]);
    int ans = 0;
    int new_min = min;
    for (int i = 1;  i < n; ++i) {
        int delta = times[i] - times[i-1];
        new_min += delta * (n) - (D);
        if (new_min < min) {
            min = new_min;
            ans = i;
        }
    }

    ans = times[ans];
    int h, m, s;
    h = ans / H;
    m = ans / M - h * M;
    s = ans - h * H - m * M;
    printf("%02d:%02d:%02d\n", h, m, s);
}
