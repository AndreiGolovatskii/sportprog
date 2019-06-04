#include <bits/stdc++.h>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>
const int MN = 1e6 + 10;
int z[MN], r = -1;
string s;
void add(char c) {
    s.push_back(c);
    int ss = s.size();
    if(r == -1) {
        r = 1;
        z[0] = MN;
        return;
    }

    if(c != s[z[r]]) {
        for(int i = r + 1; i < ss - 1; ++i) {
            int zf = min(z[i % r], ss - i - 1);
            if(s[zf] == c && zf == ss - i - 1) {
                z[i] = zf + 1;
                r = i;
                return;
            } else {
                z[i] = zf;
            }
        }
        if(c == s[0]) {
            r = ss - 1;
            z[r] = 1;
            return;
        } else {
            r = s.size();
        }
    } else {
        z[r]++;
        return;
    }
}

int get(int pos) {
    if(pos == 0) {
        return s.size();
    } else {
        return min(z[pos % r], (int)s.size() - pos);
    }
}


int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    string si;
    cin >> si;
    for(auto i : si) {
        add(i);
    }
    for(int i = 0; i < si.size(); ++i) {
        cout << get(i) << " ";
    }
//    for(int l = 0; l < 100; ++l) {
//        string si;
//        cin >> si;
//        if(si == "add") {
//            string c;
//            cin >> c;
//            for(auto ch : c) {
//                add(ch);
//            }
//            cout << s << " " << r << "\n";
//            for(int i = 0; i < s.size(); ++i) {
//                cout << get(i) << " ";
//            }
//            cout << "\n";
//        } else if(si == "get"){
//            int pos;
//            cin >> pos;
//            cout << get(pos);
//        } else if(si == "br") {
//            break;
//        }
//    }
}