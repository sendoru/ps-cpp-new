// #include "atcoder/all"
// #pragma GCC optimize("O3,Ofast,unroll-loops")
// #define DEBUG
#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll cross(const pll &a, const pll &b) {
    return a.x * b.y - a.y * b.x;
}

ll cross(ll x1, ll y1, ll x2, ll y2) {
    return x1 * y2 - y1 * x2;
}

ll dot(const pll &a, const pll &b) {
    return a.x * b.x + a.y * b.y;
}

int ccw(const pll &a, const pll &b, const pll &c) {
    // ll area = cross({b.x - a.x, b.y - a.y}, {c.x - b.x, c.y - b.y});
    ll area = cross(b.x - a.x, b.y - a.y, c.x - b.x, c.y - b.y);
    return (area > 0) - (area < 0);
}

pll pivot;

struct cmp {
    bool operator()(const pll &a, const pll &b) {
        return ccw(a, pivot, b) > 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    vector<pll> dots;

#ifdef DEBUG
    n = 500;
    dots.resize(n);
    for (int i = 0; i < n; i++) {
        dots[i] = {rand() % 100000, rand() % 100000};
    }
    sort(dots.begin(), dots.end());
    dots.erase(unique(dots.begin(), dots.end()), dots.end());
    n = dots.size();

#else
    cin >> n;
    dots.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> dots[i].x >> dots[i].y;
    }
#endif
    ll ans = 0;
    ll cand_size_sum = 0;
    for (int i = 0; i < n; i++) {
        // cout << "i: " << i << endl;
        auto dots_copy = dots;
        // dots_copy.erase(dots_copy.begin() + i);
        swap(dots_copy[i], dots_copy[n - 1]);
        dots_copy.pop_back();
        // angle sort
        sort(dots_copy.begin(), dots_copy.end(), [&](const pll &a, const pll &b) {
            double angle_a = atan2(a.y - dots[i].y, a.x - dots[i].x);
            double angle_b = atan2(b.y - dots[i].y, b.x - dots[i].x);
            return angle_a > angle_b;
        });
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            deque<pll> cand;

            for (int k = 0; k < n - 1; k++) {
                if (ccw(dots[i], dots[j], dots_copy[k]) < 0) {
                    cand.push_back(dots_copy[k]);
                }
            }
            cand_size_sum += cand.size();
            if (cand.size() < 2) {
                continue;
            }
            while (ccw(cand.back(), dots[i], cand.front()) > 0) {
                auto back = cand.back();
                cand.pop_back();
                cand.push_front(back);
            }

            // // 각 jik가 작은 순서대로
            // pivot = dots[i];
            // sort(cand.begin(), cand.end(), cmp());

            // 각 ijk가 작은 순서대로
            bool first = true;
            pll min_dot = {LLONG_MAX, LLONG_MAX};
            for (auto &c : cand) {
                if (!first && ccw(min_dot, dots[j], c) < 0) {
                    ans++;
                } else {
                    min_dot = c;
                    first = false;
                }
            }
        }
    }
    cout << ans / 3;

    return 0;
}