#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

int main() {
    //ifstream cin("build.in");
    //ofstream cout("build.out");
    int N, M, x, y;
    cin >> M >> N >> x >> y;
    long long ans;
    ans = M  - 1 + N - 1;
    ans += min(x - 1, y - 1) + min(x - 1, N - y) + min(M - x, y - 1) + min(M - x, N-y);
    cout << ans;
}
