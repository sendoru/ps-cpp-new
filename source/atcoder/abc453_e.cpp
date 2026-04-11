// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> facts;
vector<ll> inv_facts;

ll comb(ll n, ll r) {
    if (r > n || r < 0) {
        return 0;
    }
    return facts[n] * inv_facts[r] % MOD9 * inv_facts[n - r] % MOD9;
}

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    facts.resize(2e5 + 100);
    facts[0] = 1;
    for (ll i = 1; i < (ll)facts.size(); i++) {
        facts[i] = facts[i - 1] * i % MOD9;
    }

    inv_facts.resize(2e5 + 100);
    inv_facts.back() = modpow(facts.back(), MOD9 - 2, MOD9);
    for (ll i = (ll)inv_facts.size() - 2; i >= 0; i--) {
        inv_facts[i] = inv_facts[i + 1] * (i + 1) % MOD9;
    }

    ll n;
    cin >> n;
    vector<array<ll, 2>> lr(n);
    for (int i = 0; i < n; i++) {
        cin >> lr[i][0] >> lr[i][1];
    }

    vector<ll> in_a(n + 1), in_b(n + 1), in_both(n + 1);
    for (int i = 0; i < n; i++) {
        in_a[lr[i][0]]++;
        in_a[lr[i][1] + 1]--;
        in_b[n - lr[i][1]]++;
        in_b[n - lr[i][0] + 1]--;
        vector<array<ll, 2>> v = {{lr[i][0], 1}, {lr[i][1] + 1, -1}, {n - lr[i][1], 1}, {n - lr[i][0] + 1, -1}};
        sort(v.begin(), v.end());
        if (v[1][1] == 1) {
            in_both[v[1][0]]++;
            in_both[v[2][0]]--;
        }
    }
    for (int i = 1; i <= n; i++) {
        in_a[i] += in_a[i - 1];
        in_b[i] += in_b[i - 1];
        in_both[i] += in_both[i - 1];
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll in_neither = n - in_a[i] - in_b[i] + in_both[i];
        if (in_neither == 0) {
            ans += comb(in_both[i], i - in_a[i] + in_both[i]);
            ans %= MOD9;
        }
    }

    cout << ans << '\n';

    return 0;
}