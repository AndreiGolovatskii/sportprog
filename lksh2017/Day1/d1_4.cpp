#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
/**
Okey
*/

using namespace std;

bool cmp(string a, string b){
    return a + b > b + a;
}

int main() {
    ofstream cout("number.out");
    ifstream cin("number.in");
    string a;
    vector<string> Arr;
    string ans;
    int n = 0;
    while (cin >> a) {
        Arr.push_back(a);
        n++;
    }

    sort(Arr.begin(), Arr.end(), cmp);

    for (auto i : Arr) {
        ans += i;
    }
    cout << ans;
}
