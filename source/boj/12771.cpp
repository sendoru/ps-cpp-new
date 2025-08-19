// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int ccw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    ll val = (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1);
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;
}

ll foo(vector<vector<ll>> &a, ll x_o, ll y_o) {
    ll n = a.size();
    vector<vector<ll>> dots;
    for (int j = 0; j < n; j++) {
        if (a[j][2] == y_o)
            continue;
        if (a[j][2] > y_o) {
            dots.push_back({a[j][0] - x_o, a[j][2] - y_o, a[j][0] - a[j][1]});
            dots.push_back({a[j][1] - x_o, a[j][2] - y_o, a[j][1] - a[j][0]});
        } else {
            dots.push_back({a[j][0] - x_o, a[j][2] - y_o, a[j][1] - a[j][0]});
            dots.push_back({a[j][1] - x_o, a[j][2] - y_o, a[j][0] - a[j][1]});
        }
    }

    for (auto &dot : dots) {
        if (dot[1] < 0) {
            dot[0] = -dot[0];
            dot[1] = -dot[1];
        }
    }
    sort(dots.begin(), dots.end(), [](const vector<ll> &a, const vector<ll> &b) {
        int ccw_val = ccw(0, 0, a[0], a[1], b[0], b[1]);
        if (ccw_val != 0) {
            return ccw_val > 0;
        }
        return a[2] > b[2];
    });
    ll res = 0, cur = 0;
    for (int i = 0; i < (int)dots.size(); i++) {
        cur += dots[i][2];
        res = max(res, cur);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(3));
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        a[i][2] *= -1;
        if (a[i][0] > a[i][1]) {
            swap(a[i][0], a[i][1]);
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        vector<ll> cur = a[i];
        ll cur_ans = max(foo(a, cur[0], cur[2]), foo(a, cur[1], cur[2]));
        ans = max(ans, cur_ans + cur[1] - cur[0]);
    }

    cout << ans;

    return 0;
}