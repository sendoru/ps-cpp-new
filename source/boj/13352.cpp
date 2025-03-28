// #include "atcoder/all"
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

bool on_line(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    ll dx = x2 - x1;
    ll dy = y2 - y1;
    return dy * x3 - dx * y3 == dy * x1 - dx * y1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    if (n <= 4) {
        cout << "success\n";
        return 0;
    }

    vector<pll> dots(n);
    for (int i = 0; i < n; i++) {
        cin >> dots[i].x >> dots[i].y;
    }

    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dis(0, n - 1);

    for (int t = 0; t < 20000; t++) {
        int i1 = dis(gen);
        int i2 = dis(gen);
        if (i1 == i2) {
            continue;
        }
        ll x1 = dots[i1].x;
        ll y1 = dots[i1].y;
        ll x2 = dots[i2].x;
        ll y2 = dots[i2].y;

        vector<bool> mask(n, 0);
        // dy x - dx y = dy x1 - dx y1
        for (int i = 0; i < n; i++) {
            ll x = dots[i].x;
            ll y = dots[i].y;

            if (on_line(x1, y1, x2, y2, x, y)) {
                mask[i] = 1;
            }
        }

        vector<pll> remain;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (!mask[i]) {
                remain.push_back(dots[i]);
            } else {
                cnt++;
            }
        }

        if (remain.size() <= 2) {
            cout << "success\n";
            return 0;
        }
        x1 = remain[0].x;
        y1 = remain[0].y;
        x2 = remain[1].x;
        y2 = remain[1].y;
        fill(mask.begin(), mask.end(), 0);
        for (int i = 0; i < remain.size(); i++) {
            ll x = remain[i].x;
            ll y = remain[i].y;

            if (on_line(x1, y1, x2, y2, x, y)) {
                mask[i] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (mask[i]) {
                cnt++;
            }
        }

        if (cnt == n) {
            cout << "success\n";
            return 0;
        }
    }

    cout << "failure\n";

    return 0;
}