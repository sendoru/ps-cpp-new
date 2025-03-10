// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

ll cross(pll a, pll b) {
    return a.first * b.second - a.second * b.first;
}

pll sub(pll a, pll b) {
    return {a.first - b.first, a.second - b.second};
}

// {0, {0, 0}}: no intersection
// {1, {x, y}}: intersection at (x, y)
// {2, {0, 0}}: two segments are overlapped (infinite intersections)
pair<int, pld> intersect(pll p0, pll p1, pll q0, pll q1) {
    pll u = sub(p1, p0);
    pll v = sub(q1, q0);
    ll det = cross(u, v);
    if (det < 0) {
        p0.swap(p1);
        u.first *= -1;
        u.second *= -1;
        det *= -1;
    }
    if (det != 0) {
        pll w = sub(q0, p0);
        ll cross_wu = cross(w, u);
        ll cross_wv = cross(w, v);
        if (cross_wu < 0 || cross_wu > det || cross_wv < 0 || cross_wv > det) {
            return {0, {0, 0}};
        }
        ld s = (ld)cross_wv / det;
        ld t = (ld)cross_wu / det;
        return {1, {p0.first + u.first * s, p0.second + u.second * s}};
    } else {
        if (cross(sub(q0, p0), u) != 0 || cross(sub(q0, p1), u) != 0 || cross(sub(p0, q0), v) != 0 || cross(sub(p0, q1), v) != 0) {
            return {0, {0, 0}};
        }
        pll a0 = min(p0, p1);
        pll a1 = max(p0, p1);
        pll b0 = min(q0, q1);
        pll b1 = max(q0, q1);
        pll l = max(a0, b0);
        pll r = min(a1, b1);
        if (l < r) {
            return {2, {0, 0}};
        } else if (l == r) {
            return {1, {(ld)l.first, (ld)l.second}};
        }
        return {0, {0, 0}};
    }
}

int main() {
    pll p0, p1, q0, q1;
    cin >> p0.first >> p0.second >> p1.first >> p1.second >> q0.first >> q0.second >> q1.first >> q1.second;
    pair<int, pld> res = intersect(p0, p1, q0, q1);
    if (res.first == 0) {
        cout << 0;
    } else if (res.first == 1) {
        cout << 1 << '\n'
             << fixed << setprecision(12) << res.second.first << ' ' << res.second.second;
    } else {
        cout << 1;
    }

    return 0;
}