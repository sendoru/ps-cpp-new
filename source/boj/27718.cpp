// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<pll>> lines(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines[i] = {{x1, y1}, {x2, y2}};
    }
    vector<vector<int>> adj(n, vector<int>(n, 3));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto [type, p] = intersect(lines[i][0], lines[i][1], lines[j][0], lines[j][1]);
            if (type == 0) {
                adj[i][j] = adj[j][i] = 0;
            } else if (type == 1) {
                pll p_ll = {(ll)(round(p.first)), (ll)(round(p.second))};
                if (abs(p.first - p_ll.first) < 1e-4 && abs(p.second - p_ll.second) < 1e-4 && (p_ll == lines[i][0] || p_ll == lines[i][1] || p_ll == lines[j][0] || p_ll == lines[j][1])) {
                    adj[i][j] = adj[j][i] = 1;
                } else {
                    adj[i][j] = adj[j][i] = 2;
                }
            } else if (type == 2) {
                adj[i][j] = adj[j][i] = 3;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j];
        }
        cout << '\n';
    }

    return 0;
}
