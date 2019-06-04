#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct edge {
    int v, cost, weight;
};

const int DAY = 24 * 60;
const int START = 0;

bool f(int weight, vector<vector<edge>> &g, int n) {
    vector<int> dist(n, 1e9);
    dist[START] = 0;
    set<pair<int, int>> q;

    q.insert({dist[START], START});

    while (!q.empty()) {
        int v = q.begin() -> second;
        q.erase(q.begin());
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i].v;
            int w = g[v][i].weight;
            int cost = g[v][i].cost;
            if (dist[v] + cost < dist[to] && w >= weight) {
                q.erase({dist[to], to});
                dist[to] = dist[v] + cost;
                q.insert({dist[to], to});
            }
        }
    }
    if (dist[n - 1] > DAY) {
        return false;
    } else {
        return true;
    }
}


int main() {
    int m, n;
    cin >> n >> m;
    vector<vector<edge>> g(n);
    int max_weight = 0;
    for (int i = 0; i < m; ++i) {
        int v, u, cost, weight;
        max_weight = max(weight, max_weight);
        cin >> v >> u >> cost >> weight;
        v--;
        u--;
        edge e;
        e.cost = cost;
        e.v = u;
        e.weight = weight;
        g[v].push_back(e);
        e.v = v;
        g[u].push_back(e);
    }

    double right = max_weight;
    double left = 0;
    for (int i = 0; i < 100; ++i) {
        double mid = (left + right) / 2;
        if (!f(mid, g, n)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << max((int)(right - 3 * 1000 * 1000) / 100, 0);
}
