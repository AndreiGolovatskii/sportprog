#include <iostream>
#include <set>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>

using namespace std;

bool f(int x, vector<int> &Arr, int k){
    for (auto i : Arr){
        k -= i / x;
    }
    return k <= 0;
}


int main() {
    ofstream cout("ropes.out");
    ifstream cin("ropes.in");
    int n, k;
    long long sum = 0;
    cin >> n >> k;
    vector<int> Arr(n);
    for (int i=0; i < n; ++i) {
        cin >> Arr[i];
        sum += Arr[i];
    }
    if (k > sum) {
        cout << 0;
        return 0;
    }
    int left = 0;
    int right = 1e9;
    for (int i=0; i < 1e2; ++i) {
        int mid = (left + right) / 2;
        if (f(mid, Arr, k))
            left = mid;
        else
            right = mid;
    }
    cout << left;
}
