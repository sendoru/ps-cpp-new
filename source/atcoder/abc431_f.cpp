// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll facts[1'000'010];

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = (res * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

ll comb(ll n, ll r) {
    ll numer = facts[n];
    ll denom = (facts[r] * facts[n - r]) % MOD9;
    return (numer * modpow(denom, MOD9 - 2, MOD9)) % MOD9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    facts[0] = 1;
    for (int i = 1; i <= 1'000'000; i++) {
        facts[i] = (facts[i - 1] * i) % MOD9;
    }

    ll n, d;
    cin >> n >> d;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> cnt(*max_element(a.begin(), a.end()) + 1, 0);
    for (auto &x : a) {
        cnt[x]++;
    }

    ll ans = 1;
    ll window_sum = 0;
    for (int i = 0; i < cnt.size(); i++) {
        if (i > d) {
            window_sum -= cnt[i - d - 1];
        }
        ans = (ans * comb(window_sum + cnt[i], cnt[i])) % MOD9;
        window_sum += cnt[i];
    }

    cout << ans;

    return 0;
}