#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

const int INF = 1e9;
const int MAX_SIZE = 10000;
const int S = 1000;
const int T = 10;

int perm(int k, int type) {
    if (type == 0 && k < 9000) {
        return k + S;
    } else if (type == 1 && k % T > 1) {
        return k - 1;
    } else if (type == 2) {
        return k / S + (k % S) * T;
    } else if (type == 3) {
        return k / T + (k % T) * S;
    }
    return k;
}


int main() {
    int start, finish;
    cin >> start >> finish;

    vector<int> used(MAX_SIZE, INF);
    vector<int> p(MAX_SIZE, 0);
    used[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int new_k = perm(curr, i);
            if (used[new_k] > used[curr] + 1) {
                q.push(new_k);
                used[new_k] = used[curr] + 1;
                p[new_k] = curr;
            }
        }
    }

    stack<int> ans;
    ans.push(finish);
    while (finish != start) {
        finish = p[finish];
        ans.push(finish);
    }
    while (!ans.empty()) {
        cout << ans.top() << endl;
        ans.pop();
    }
}
