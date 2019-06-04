#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>


using namespace std;

const int p = 8;
const int Ox[p] = {1, 1, 1, 0, 0, -1, -1, -1};
const int Oy[p] = {1, 0, -1, 1, -1, 1, 0, -1};

bool under_att(vector<vector<int>> &rooks, int xK, int yK) {
    for (auto &i : rooks) {
        if ((i[0] == xK) xor (i[1] == yK))
            return true;
    }
    return false;
}

int main() {
    string s;
    cin >> s;
    int xK = s[0] - 'a';
    int yK = s[1] - '1';

    int n;
    cin >> n;
    vector<vector<int>> rooks(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int x1 = s[0] - 'a';
        int y1 = s[1] - '1';
        rooks[i][0] = x1;
        rooks[i][1] = y1;
    }
    for (int i = 0; i < p; ++i) {
        int nx = xK + Ox[i];
        int ny = yK + Oy[i];
        if (nx < 0 || nx >= p || ny < 0 || ny >= p)
            continue;
        if (!under_att(rooks, nx, ny)) {
            char x = 'a' + nx;
            char y = '1' + ny;
            cout << x << y <<"\n";
            exit(0);
        }
    }
    if (!under_att(rooks, xK, yK))
        cout << "Stalemate";
    else
        cout << "Checkmate";
}
