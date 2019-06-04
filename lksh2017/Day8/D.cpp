#include  <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if ((n % 2) * (m % 2))
        cout << 2;
    else
        cout << 1;

}

