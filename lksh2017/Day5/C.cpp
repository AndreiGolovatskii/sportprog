#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>

using namespace std;

bool is_open(char a) {
    return (a == (char)40);
}


int main() {
    ofstream cout("erase.out");
    ifstream cin("erase.in");
    int count = 0, ans=0;
    char a;
    while (cin >> a) {
        if (is_open(a))
            count ++;
        else {
            if (count > 0)
                count--;
            else
                ans++;
        }
    }
    ans += count;
    cout << ans;
}
