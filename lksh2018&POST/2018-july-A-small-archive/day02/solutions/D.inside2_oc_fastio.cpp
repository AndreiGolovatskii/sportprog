/** Olha Chernikova */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

typedef long long lld;

const lld INF = 1e9 + 10;
const int maxn = 1e5 + 10;


struct Point {
    lld x, y;
    Point(){}
    Point(lld _x, lld _y) {
        x = _x;
        y = _y;
    }
};

bool operator <(Point A, Point B) {
    return (A.x < B.x || (A.x == B.x && A.y < B.y));
}

bool operator == (Point A, Point B) {
    return (A.x == B.x) && (B.y == A.y);
}

Point operator -(Point A, Point B) {
    return Point(A.x - B.x, A.y - B.y);
}

struct Line {
    lld a, b, c;
    Line(){}
    Line(Point A, Point B) {
        a = -A.y + B.y;
        b = A.x - B.x;
        c = -a * A.x - b * A.y;
    }
    lld dist(Point A) {
        return fabs(a * A.x + b * A.y + c);
    }
};


struct Segment {
    int fl, id;
    Point St, Fn;
    Segment(){}
    Segment(Point A, Point B, int _id = 0){
        fl = 0;
        if (B < A) {
            fl = 1;
            swap(A, B);
        }
        St = A;
        Fn = B;
        id = _id;
    }
};

// ostream& operator << (ostream & out, Segment & S) {
//     out << S.St.x << " " << S.St.y << " " << S.Fn.x << " " << S.Fn.y;
//     return out;
// }

bool Point_in_segment(Segment A, Point B) {
    Line A1(A.St, A.Fn);
    if (A1.dist(B) == 0) {
        if (B.x <= A.Fn.x && B.x >= A.St.x) return 1;
        else return 0;
    }
    else return 0;
}

pair<lld, lld> mul(pair <lld, lld> A, lld b) {
    pair <lld, lld> res = A;
    res.first *= b;
    res.second *= b;
    res.first += res.second/INF;
    res.second %= INF;
    return res;
}

int sgn(lld a, lld b, lld c, lld d) {
    if (a < 0 && c > 0) return -1;
    if (a > 0 && c < 0) return 1;
    int fl = 1;
    if (a < 0) {
        fl = -1;
        a = -a;
        c = -c;
    }
    pair <lld, lld> res1 = mul(make_pair(a/INF, a%INF), b);
    pair <lld, lld> res2 = mul(make_pair(c/INF, c%INF), d);
    if (res1 < res2) return -1*fl;
    if (res2 < res1) return 1*fl;
    return 0;           
}

pair<lld, lld> y_in_line(Segment A, lld x) {
    Line A1(A.St, A.Fn);
    pair<lld, lld> res;
    res.first = (-A1.a * x - A1.c);
    res.second = A1.b;
    if (A1.b == 0) {
        res.second = 1;
        res.first = A.St.y;  
    }
    if (A1.b < 0) {
        res.second = -res.second;
        res.first = -res.first;
    }
    return res;
}

bool operator < (Segment A, Segment B) {
    if (A.id == B.id) return 0;

    if (A.St == A.Fn) {
        if (Point_in_segment(B, A.St)) {
            return 1;
        }
    }
    
    if (B.St == B.Fn) {
        if (Point_in_segment(A, B.St)) {
            return 0;
        }
    }  
    lld Cur_x = (max(A.St.x, B.St.x) + min(A.Fn.x, B.Fn.x))/2;
    pair<lld, lld> Y1 = y_in_line(A, Cur_x), Y2 = y_in_line(B, Cur_x);
    if (sgn(Y1.first, Y2.second, Y2.first, Y1.second) < 0)
        return 1;
    else if (sgn(Y1.first, Y2.second, Y2.first, Y1.second) > 0)
        return 0;
    else 
        return A.St.x + A.Fn.x < B.St.x + B.Fn.x;
}


lld c_p(Point A, Point B) {
    if (A.x * B.y - A.y * B.x < 0) return -1;
    else if (A.x * B.y - A.y * B.x) return 1;
    else return 0;
}

struct Ask {
    Segment Seg;
    lld flag;
    Ask(){}
    Ask(Segment Seg, lld flag): Seg(Seg), flag(flag){}
};

bool operator < (Ask A, Ask B)
{
    Point A1, B1;
    if (A.flag == 0 || A.flag == 1) A1 = A.Seg.St;
    else A1 = A.Seg.Fn;
    if (B.flag == 0 || B.flag == 1) B1 = B.Seg.St;
    else B1 = B.Seg.Fn;
    return (A1 < B1) || (A1 == B1 && A.flag < B.flag);
}

int FL = 0;

bool Ins(Segment A) {
    if (A.fl == 1){
        swap(A.St, A.Fn);
    }
    if (FL == 1) {
        swap(A.St, A.Fn);
    }
    if (A.St.x >= A.Fn.x) return 1;
    return 0; 
}

set <Segment> Set;
vector <Ask> As;

int res[maxn];
int N;
  

lld S() {
    lld res = 0;
    for (int i = 0; i < 2*N; i += 2) {
        Point Bg = As[i].Seg.St, Ed = As[i].Seg.Fn;
        if (As[i].Seg.fl == 1) {
            swap(Bg, Ed);
        }

        res += (Bg.x - Ed.x)*(Bg.y + Ed.y)/2;
    } 
    return res;
}


void Do() {
    Set.clear();
    As.resize(0);
    FL = 0;
    N = readInt();
    Point A, B, Fr;
    A.x = readInt() * 2;
    A.y = readInt() * 2;
    Fr = A;
    B = A;
    for (lld i = 0; i < N - 1; ++i) {
        A = B;
        B.x = readInt() * 2;
        B.y = readInt() * 2;
        Ask A2(Segment(A, B, i), 0);
        As.push_back(A2);
        A2.flag = 2;
        As.push_back(A2);
    }
    A = Fr;
    Ask A2(Segment(B, A, N), 0);
    As.push_back(A2);
    A2.flag = 2;
    As.push_back(A2);
    
    if (S() < 0) FL = 1;
       
    int K = readInt();
    for (int i = 0; i < K; ++i) {
        Point C;
        C.x = readInt() * 2;
        C.y = readInt() * 2;
        Ask A2;
        Segment A1(C, C);
        A1.id = i + N + 1;
        A2.Seg = A1;
        A2.flag = 1;
        As.push_back(A2);
    }
    
    Segment A1(Point(-2*INF, 2*INF), Point(2*INF, 2*INF));
    A1.id = -1;
    Set.insert(A1);
    A1 = Segment(Point(-2*INF, -2*INF), Point(2*INF, -2*INF));
    A1.id = -2;
    Set.insert(A1);
    
    sort(As.begin(), As.end());
    
    
    lld cur_x = -INF;
    multiset<lld> cur_y;
    
    for (lld i = 0; i < As.size(); ++i) {
        if (As[i].flag == 0) {
            if (As[i].Seg.St.x == As[i].Seg.Fn.x) { 
                cur_x = As[i].Seg.St.x;
                cur_y.insert(As[i].Seg.St.y);
                cur_y.insert(As[i].Seg.Fn.y);
                continue;
            }
            Set.insert(As[i].Seg);
        }
        else if (As[i].flag == 2) {
            if (As[i].Seg.St.x == As[i].Seg.Fn.x) {
                cur_y.erase(cur_y.find(As[i].Seg.St.y));
                cur_y.erase(cur_y.find(As[i].Seg.Fn.y));
                continue;
            }
            Set.erase(As[i].Seg);
        } else {
            Segment A1 = *Set.upper_bound(As[i].Seg);
            if (cur_x == As[i].Seg.St.x && cur_y.size() > 0 && *cur_y.rbegin() >= As[i].Seg.St.y) {
                res[As[i].Seg.id - N - 1] = 2;
            }
            else if (Point_in_segment(A1, As[i].Seg.St)) {
                res[As[i].Seg.id - N - 1] = 2;
            }
            else if (A1.Fn.x == 2*INF) {
                res[As[i].Seg.id - N - 1] = 0;
            } else if (Ins(A1)) {
                res[As[i].Seg.id - N - 1] = 1;
            } else {
                res[As[i].Seg.id - N - 1] = 0;
            }
        }
    }
    
    for (int i = 0; i < K; ++i) {
        if (res[i] == 1) {
            puts("INSIDE");
        } else if (res[i] == 2) {
            puts("BORDER");
        } else {
            puts("OUTSIDE");
        }
    }
}

int main() {
    int T = readInt();
    for (int test = 0; test < T; ++test) {
        Do();
    }
}
