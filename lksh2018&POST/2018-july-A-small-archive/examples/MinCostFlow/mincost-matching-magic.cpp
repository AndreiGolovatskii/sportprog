/** PTZ 2015.02, MIPT Unknown (Savinov, ...) */

#include "bits/stdc++.h"

#define clr(x) memset((x), 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define in(x) int (x); input((x));
#define x first
#define y second
#define itn int

#define next next12345
#define prev prev12345
#define x1 x12345
#define y1 y12345

using namespace std;

template <typename T>
T gcd(T x, T y) {
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

template <class _T> inline _T sqr(const _T& x) {return x * x;}
template <class _T> inline string tostr(const _T& a) {ostringstream os(""); os << a; return os.str();}

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef pair < int, int > PII;
const long double PI = 3.1415926535897932384626433832795L;

template<typename T>
inline void input(T &a) {
    static int c;
    a = 0;
    while (!isdigit(c = getchar()) && c != '-') {}
    char neg = 0;
    if (c == '-') {
        neg = 1;
        c = getchar();
    }
    while (isdigit(c)) {
        a = 10 * a + c - '0';
        c = getchar();
    }
    if (neg) a = -a;
}

template <typename T = int>
inline T nxt() {
    T res;
    input(res);
    return res;
}

const int N = 500;

typedef long long int64;

int width;
int height;
int64 matrix[N][N];
int sol[N];
int row[N];
int64 result;
const int alpha = 7;
int64 cost_scaling_factor;
const int minEpsilon = 1;
int64 epsilon;
int64 largest_scaled_cost_magnitude;
int64 price[N];
vector<int> active_nodes;

void updateEpsilon() {
    epsilon = (epsilon + alpha - 1) / alpha;
}

inline int64 partialReducedCost(int from, int to) {
    return matrix[from][to] - price[to];
}

static inline  __attribute__ ((always_inline))
void calcBestAndGap(int source, int& best, int64& gap) {
    best = 0;
    int64 min_cost = partialReducedCost(source, 0);
    int64 second_min_cost = 1LL << 62;
    for (int i = 1; i < width; i++) {
        int64 cost = partialReducedCost(source, i);
        if (cost < min_cost) {
            best = i;
            second_min_cost = min_cost;
            min_cost = cost;
        } else if (cost < second_min_cost) {
            second_min_cost = cost;
        }
    }
    gap = second_min_cost - min_cost;
}

void double_push(int source) {
    int best = 0;
    int64 gap = 0;
    calcBestAndGap(source,best,gap);
    int from = row[best];
    if (from != -1) {
        sol[from] = -1;
        active_nodes.push_back(from);
    }
    sol[source] = best;
    row[best] = source;
    price[best] -= gap + epsilon;
}

void refine() {
    fill(sol, sol + height, -1);
    fill(row, row + width, -1);
    active_nodes.clear();
    for (int i = 0; i < height; i++) {
        active_nodes.push_back(i);
    }
    while (!active_nodes.empty()) {
        int source = active_nodes.back();
        active_nodes.pop_back();
        double_push(source);
    }
}

void init() {
    cost_scaling_factor = 1 + max(width, height);
    fill(sol, sol + height, -1);
    fill(row, row + width, -1);
    fill(price, price + width, 0);
    largest_scaled_cost_magnitude = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] *= cost_scaling_factor;
            largest_scaled_cost_magnitude = max(largest_scaled_cost_magnitude,
                    llabs(matrix[i][j]));
        }
    }
    epsilon = largest_scaled_cost_magnitude;

    if (epsilon == 0) {
        for (int i = 0; i < height; i++) {
            sol[i] = i;
            row[i] = i;
        }
        return;
    }
}

void solve() {
    while (epsilon > 1) {
        updateEpsilon();
        refine();
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    #define fname "banach"
    freopen(fname".in", "r", stdin);
    freopen(fname".out", "w", stdout);
#endif

    /** Исходная задача */
    int n = nxt();
    long long ax[n], ay[n];
    long long bx[n], by[n];

    for (int i = 0; i < n; ++i) {
        ax[i] = nxt(), ay[i] = nxt();
    }

    for (int i = 0; i < n; ++i) {
        bx[i] = nxt(), by[i] = nxt();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = -ax[i] * bx[j] - ay[i] * by[j];
        }
    }

    /** Теперь нужно найти паросочетание минимального веса в двудольном графе на квадратной матрице */
    width = height = n;
    init();
    solve();
    printf("Yes\n");

    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%d", sol[i] + 1);
    }
    cout << "\n";




#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC * 1000 << " ms." << endl;
#endif
    return 0;
};