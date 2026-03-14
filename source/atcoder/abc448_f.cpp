// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MAX_COORD = 2e7 + 1;

struct Query {
    int idx;
    ll x, y;
};

// hilbert curve order
ll hilbert_order(ll x, ll y, int k) {
    ll res = 0;
    for (ll s = 1 << (k - 1); s > 0; s >>= 1) {
        ll rx = (x & s) > 0;
        ll ry = (y & s) > 0;
        res += s * s * ((3 * rx) ^ ry);
        if (ry == 0) {
            if (rx == 1) {
                x = s - 1 - x;
                y = s - 1 - y;
            }
            swap(x, y);
        }
    }
    return res;
}

ll dist(const Query &a, const Query &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<Query> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].idx = i;
    }

    int k = 0;
    while ((1LL << k) < MAX_COORD) {
        k++;
    }
    sort(points.begin() + 1, points.end(), [&](const Query &a, const Query &b) {
        return hilbert_order(a.x, a.y, k) < hilbert_order(b.x, b.y, k);
    });

    // 2-opt heuristic
    for (ll i = 2; i < n - 1; i++) {
        for (ll j = i + 1; j < min(n, i + 100); j++) {
            ll before = dist(points[i - 1], points[i]) + dist(points[j], points[(j + 1) % n]);
            ll after = dist(points[i - 1], points[j]) + dist(points[i], points[(j + 1) % n]);
            if (after < before) {
                reverse(points.begin() + i, points.begin() + j + 1);
            }
        }
    }

    deque<int> ans;
    for (int i = 0; i < n; i++) {
        ans.push_back(points[i].idx);
    }
    while (ans.front() != 0) {
        ans.push_back(ans.front());
        ans.pop_front();
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }

    return 0;
}