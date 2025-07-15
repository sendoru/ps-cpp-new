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

    int n, m;
    cin >> n >> m;
    vector<ll> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    vector<ll> dists;
    for (int i = 1; i < x.size(); i++) {
        dists.push_back(x[i] - x[i - 1]);
    }
    sort(dists.begin(), dists.end());
    ll ans = x.back() - x.front();
    for (int i = 0; i < m - 1 && !dists.empty(); i++) {
        ans -= dists.back();
        dists.pop_back();
    }

    cout << ans << endl;

    return 0;
}