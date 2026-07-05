// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> facts(200'100);
vector<ll> inv_facts(200'100);

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll x, ll m) {
    return modpow(x, m - 2, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    facts[0] = 1;
    for (int i = 1; i < (int)facts.size(); i++) {
        facts[i] = facts[i - 1] * i % MOD9;
    }
    inv_facts.back() = modinv(facts.back(), MOD9);
    for (int i = (int)inv_facts.size() - 2; i >= 0; i--) {
        inv_facts[i] = inv_facts[i + 1] * (i + 1) % MOD9;
    }

    int t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<vector<ll>> segments;
        vector<ll> cur_segment;
        cur_segment.push_back(a[0]);
        for (int i = 1; i < n; i++) {
            if (a[i] % k == a[i - 1] % k || a[i] % k == (k - a[i - 1] % k) % k) {
                cur_segment.push_back(a[i]);
            } else {
                segments.push_back(cur_segment);
                cur_segment.clear();
                cur_segment.push_back(a[i]);
            }
        }
        if (!cur_segment.empty()) {
            segments.push_back(cur_segment);
        }

        ll ans = 1;

        for (auto &segment : segments) {
            ll rem = segment[0] % k;

            if (rem == 0 || rem == k - rem) {
                map<ll, ll> freq;
                for (ll x : segment) {
                    freq[x]++;
                }
                ans = ans * facts[segment.size()] % MOD9;
                for (auto &[_, f] : freq) {
                    ans = ans * inv_facts[f] % MOD9;
                }
            }

            else {
                array<ll, 2> freq = {0, 0};
                for (auto &x : segment) {
                    freq[x % k == rem]++;
                }
                ans = ans * facts[segment.size()] % MOD9;
                ans = ans * inv_facts[freq[0]] % MOD9;
                ans = ans * inv_facts[freq[1]] % MOD9;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}