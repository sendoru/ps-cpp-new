// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ld cross(pld a, pld b) {
    return a.first * b.second - a.second * b.first;
}

pld sub(pld a, pld b) {
    return {a.first - b.first, a.second - b.second};
}

// {0, {0, 0}}: no intersection
// {1, {x, y}}: intersection at (x, y)
// {2, {0, 0}}: two segments are overlapped (infinite intersections)
pair<int, pld> intersect(pld p0, pld p1, pld q0, pld q1) {
    pld u = sub(p1, p0);
    pld v = sub(q1, q0);
    ld det = cross(u, v);
    if (det < 0) {
        p0.swap(p1);
        u.first *= -1;
        u.second *= -1;
        det *= -1;
    }
    if (det != 0) {
        pld w = sub(q0, p0);
        ld cross_wu = cross(w, u);
        ld cross_wv = cross(w, v);
        if (cross_wu < 0 || cross_wu > det || cross_wv < 0 || cross_wv > det) {
            return {0, {0, 0}};
        }
        ld s = cross_wv / det;
        ld t = cross_wu / det;
        return {1, {p0.first + u.first * s, p0.second + u.second * s}};
    } else {
        if (cross(sub(q0, p0), u) != 0 || cross(sub(q0, p1), u) != 0 || cross(sub(p0, q0), v) != 0 || cross(sub(p0, q1), v) != 0) {
            return {0, {0, 0}};
        }
        pld a0 = min(p0, p1);
        pld a1 = max(p0, p1);
        pld b0 = min(q0, q1);
        pld b1 = max(q0, q1);
        pld l = max(a0, b0);
        pld r = min(a1, b1);
        if (l < r) {
            return {2, {0, 0}};
        } else if (l == r) {
            return {1, {(ld)l.first, (ld)l.second}};
        }
        return {0, {0, 0}};
    }
}

int ccw(pld p1, pld p2, pld p3) {
    ld c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if (c > 0) {
        return 1; // counter-clockwise
    } else if (c < 0) {
        return -1; // clockwise
    } else {
        return 0; // collinear
    }
}

bool is_inside(vector<pii> &dots, int x, int y) {
    vector<pld> intersections;
    for (int i = 0; i < dots.size(); i++) {
        int x1 = min(dots[i].x, dots[(i + 1) % dots.size()].x);
        int x2 = max(dots[i].x, dots[(i + 1) % dots.size()].x);
        int y1 = min(dots[i].y, dots[(i + 1) % dots.size()].y);
        int y2 = max(dots[i].y, dots[(i + 1) % dots.size()].y);
        int ccw_val = ccw(dots[i], dots[(i + 1) % dots.size()], {x, y});
        if (ccw_val == 0 && x1 <= x && x <= x2 && y1 <= y && y <= y2) {
            return true;
        } else {
            auto [flag, intersection] = intersect({dots[i].x, dots[i].y}, {dots[(i + 1) % dots.size()].x, dots[(i + 1) % dots.size()].y}, {x + 1e-4, y + 1e-4}, {x + 1e-4, 2e9});
            if (flag == 1) {
                intersection.first = round(intersection.first * 1e6);
                intersection.second = round(intersection.second * 1e6);
                intersections.push_back(intersection);
            }
        }
    }
    sort(intersections.begin(), intersections.end());
    intersections.erase(unique(intersections.begin(), intersections.end()), intersections.end());
    if (intersections.size() % 2 == 1) {
        return true;
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pii> dots(n);
    for (int i = 0; i < n; i++) {
        cin >> dots[i].x >> dots[i].y;
    }

    vector<int> ans;
    for (int i = 0; i < 3; i++) {
        int x, y;
        cin >> x >> y;
        ans.push_back(is_inside(dots, x, y));
    }

    for (int i = 0; i < 3; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}