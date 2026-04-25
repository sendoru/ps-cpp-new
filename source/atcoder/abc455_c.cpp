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

    ll n, k;
    cin >> n >> k;
    map<ll, ll> freq;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        freq[a]++;
    }

    vector<ll> weights;
    for (auto &[a, f] : freq) {
        weights.push_back(a * f);
    }
    sort(weights.begin(), weights.end());
    ll ans = 0;
    for (int i = 0; i < (ll)weights.size() - k; i++) {
        ans += weights[i];
    }

    cout << ans;

    return 0;
}