// #include "atcoder/all"
#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef __int128_t i128;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Rational {
    i128 p, q;

    Rational(i128 p, i128 q) : p(p), q(q) {
        if (q < 0) {
            this->p = -p;
            this->q = -q;
        }
    }

    bool operator<(const Rational &other) const {
        return p * other.q < other.p * q;
    }

    bool operator>(const Rational &other) const {
        return p * other.q > other.p * q;
    }

    bool operator==(const Rational &other) const {
        return p * other.q == other.p * q;
    }

    bool operator<=(const Rational &other) const {
        return p * other.q <= other.p * q;
    }

    bool operator>=(const Rational &other) const {
        return p * other.q >= other.p * q;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll p1, q1, p2, q2;
        cin >> p1 >> q1 >> p2 >> q2;

        // find min q s.t. p1 / q1 < p / q < p2 / q2 exists

        Rational r1(p1, q1), r2(p2, q2);
        Rational s(0, 1), e(1, 0);
        while (true) {
            Rational mid((s.p + e.p), (s.q + e.q));
            if (mid <= r1) { // 오른쪽
                // (s.p + k * e.p) / (s.q + k * e.q) > p1 / q1인 최소의 k를 찾기
                ll ks = 1, ke = 1;
                while (Rational(s.p + ke * e.p, s.q + ke * e.q) <= r1) {
                    ke *= 2;
                }
                while (ks <= ke) {
                    ll kmid = (ks + ke) / 2;
                    if (Rational(s.p + kmid * e.p, s.q + kmid * e.q) <= r1) {
                        ks = kmid + 1;
                    } else {
                        ke = kmid - 1;
                    }
                }
                s = Rational(s.p + ke * e.p, s.q + ke * e.q);
            } else if (mid >= r2) { // 왼쪽
                ll ks = 1, ke = 1;
                while (Rational(ke * s.p + e.p, ke * s.q + e.q) >= r2) {
                    ke *= 2;
                }
                while (ks <= ke) {
                    ll kmid = (ks + ke) / 2;
                    if (Rational(kmid * s.p + e.p, kmid * s.q + e.q) >= r2) {
                        ks = kmid + 1;
                    } else {
                        ke = kmid - 1;
                    }
                }
                e = Rational(ke * s.p + e.p, ke * s.q + e.q);
            } else {
                cout << (ll)mid.q << "\n";
                break;
            }
        }
    }
    return 0;
}