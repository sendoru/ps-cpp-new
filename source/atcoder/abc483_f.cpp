// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll THRES = 1000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    ll q;
    cin >> q;
    vector<ll> xs(q);
    for (int i = 0; i < q; i++) {
        cin >> xs[i];
    }

    ll max_x = *max_element(xs.begin(), xs.end());

    vector<ll> larges(max_x + 1);
    vector<vector<ll>> smalls(THRES, vector<ll>(THRES));
    for (ll i = 0; i < n; i++) {
        if (b[i] >= THRES) {
            for (ll j = (b[i] - a[i]) % b[i]; j <= max_x; j += b[i]) {
                larges[j] += b[i];
            }
        } else {
            smalls[b[i]][(b[i] - a[i]) % b[i]] += b[i];
        }
    }

    vector<ll> ans(max_x + 1);
    ans[0] = accumulate(a.begin(), a.end(), 0ll);
    for (ll i = 1; i <= max_x; i++) {
        ans[i] = ans[i - 1] + n;
        ans[i] -= larges[i];
        for (ll j = 1; j < THRES; j++) {
            ans[i] -= smalls[j][i % j];
        }
    }

    for (auto x : xs) {
        cout << ans[x] << "\n";
    }

    return 0;
}