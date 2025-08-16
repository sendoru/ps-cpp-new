// #include "atcoder/all"
#include <bits/stdc++.h>

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

    int n;
    cin >> n;
    vector<int> xs, ys;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        xs.push_back(x);
        ys.push_back(y);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    ll x_diff = xs.back() - xs.front();
    ll y_diff = ys.back() - ys.front();

    ll ans = max((x_diff + 1) / 2, (y_diff + 1) / 2);
    cout << ans;

    return 0;
}