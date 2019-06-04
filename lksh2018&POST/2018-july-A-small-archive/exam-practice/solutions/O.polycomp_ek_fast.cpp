#include <bits/stdc++.h>

using namespace std;

struct Polynom {
private:
    struct MyVector : public vector <int> {
        int& operator[] (int index) {
            return at(index);
        }

        const int& operator[] (int index) const {
            return at(index);
        }
    };

    static const int K = 32;
    int deg;
    MyVector bits;
public:
    Polynom(int number = 0) {
        deg = -1;
        bits.clear();
        ensureDegree(0);
        bits[0] = number & 1;
    }

    void read() {
        bits.clear();
        deg = -1;

        int n;
        scanf("%d", &n);
        ensureDegree(n);
        for (int i = 0; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            bits[i / K] |= (x << (i % K));
        }
    }

    int operator[] (int i) const {
        return (bits[i / K] >> (i % K)) & 1;
    }

    int degree() const {
        return deg;
    }

    void print() const {
        printf("%d", degree());
        for (int i = 0; i <= degree(); ++i) {
            printf(" %d", (*this)[i]);
        }
        printf("\n");
    }

    Polynom& operator += (const Polynom & p) {
        ensureDegree(p.degree());
        for (int i = 0; i < int(p.bits.size()); ++i) {
            bits[i] ^= p.bits[i];
        }
        normalizeDegree();
        return *this;
    }

    Polynom& operator *= (const Polynom & p) {
        return *this = *this * p;
    }

    Polynom& operator %= (const Polynom & p) {
        return *this = *this % p;
    }

    Polynom operator * (const Polynom & q) const {
        const Polynom & p = *this;
        Polynom res;
        res.ensureDegree(p.degree() + q.degree());
        for (int i = 0; i <= p.degree(); ++i) {
            if (!p[i]) {
                continue;
            }
            res.xorWithShifted(q, i);
        }
        res.normalizeDegree();
        return res;
    }

    Polynom operator % (const Polynom & q) const {
        Polynom p = *this;
        for (int i = p.degree(); i >= q.degree(); --i) {
            if (!p[i]) {
                continue;
            }
            p.xorWithShifted(q, i - q.degree());
        }
        p.normalizeDegree();
        return p;
    }

private:
    void xorWithShifted(const Polynom & p, int shift) {
        if (shift % K == 0) {
            for (int i = 0, j = shift / K; i < int(p.bits.size()); ++i, ++j) {
                bits[j] ^= p.bits[i];
            }
        } else {
            int len1 = K - shift % K;
            int len2 = K - len1;
            int mask1 = (1 << len1) - 1;
            int mask2 = (1 << len2) - 1;
            for (int i = 0, j = shift / K; i < int(p.bits.size()); ++i, ++j) {
                int val = ((p.bits[i] & mask1) << len2);
                if (val) {
                    bits[j] ^= val;
                }
                val = ((p.bits[i] >> len1) & mask2);
                if (val) {
                    bits[j + 1] ^= val;
                }
            }
        }
    }

    void ensureDegree(int newDeg) {
        if (deg < newDeg) {
            deg = newDeg;
            bits.reserve((deg + K) / K);
            while (int(bits.size()) * K < deg + 1) {
                bits.push_back(0);
            }
        }
    }

    void normalizeDegree() {
        while (int(bits.size()) > 1 && bits.back() == 0) {
            bits.pop_back();
        }
        deg = int(bits.size()) * K - 1;
        while (deg > 0 && (*this)[deg] == 0) {
            --deg;
        }
    }
};

int main() {
    Polynom f, g, h;
    f.read();
    g.read();
    h.read();

    g %= h;

    const int K = (int)sqrt(f.degree() + 0.0) + 2;

    vector <Polynom> pows;
    pows.reserve(K + 1);
    pows.push_back(Polynom(1));
    for (int i = 1; i <= K; ++i) {
        pows.push_back((pows.back() * g) % h);
    }

    Polynom result(0);
    Polynom kPowG(1);
    for (int i = 0; i <= f.degree(); i += K) {
        Polynom t;
        for (int j = 0; j < K && i + j <= f.degree(); ++j) {
            if (f[i + j]) {
                t += pows[j];
            }
        }
        result += t * kPowG;
        (kPowG *= pows[K]) %= h;
    }
    result %= h;
    result.print();
 }
