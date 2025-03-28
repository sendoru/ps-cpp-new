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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, p;
    cin >> n >> p;
    if (n <= 2) {
        cout << "possible\n";
        return 0;
    }
    int target = n * p;
    if (target % 100 == 0) {
        target /= 100;
    } else {
        target = target / 100 + 1;
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

        ll dx = x2 - x1;
        ll dy = y2 - y1;

        int cnt = 0;
        // dy x - dx y = dy x1 - dx y1
        for (int i = 0; i < n; i++) {
            ll x = dots[i].x;
            ll y = dots[i].y;

            if (dy * x - dx * y == dy * x1 - dx * y1) {
                cnt++;
            }
        }

        if (cnt >= target) {
            cout << "possible\n";
            return 0;
        }
    }

    cout << "impossible\n";

    return 0;
}