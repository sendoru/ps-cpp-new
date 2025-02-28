// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll HASH_BASE = 37;

ll modpow(ll b, ll e, ll mod)
{
    ll ret = 1;
    while (e) {
        if (e & 1)
            ret = ret * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, l, k;
    cin >> n >> l >> k;
    vector<string> s(n);
    vector<int> ans(n);
    vector<ll> hash(n);

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < l; j++) {
            hash[i] += (s[i][j] - 'a' + 1) * modpow(HASH_BASE, j, MOD9);
            hash[i] %= MOD9;
        }
    }

    map<ll, vector<ll>> by_hash;
    for (int i = 0; i < n; i++) {
        by_hash[hash[i]].push_back(i);
    }
    for (auto [h, v] : by_hash) {
        for (auto i : v) {
            ans[i] = v.size();
        }
    }

    for (int i = 0; i < k; i++) {
        int p1, w1, p2, w2;
        cin >> p1 >> w1 >> p2 >> w2;
        p1--;
        p2--;
        w1--;
        w2--;
        if (s[p1][w1] == s[p2][w2]) {
            continue;
        }

        if (p1 == p2) {
            // remove from by_hash
            by_hash[hash[p1]].erase(find(by_hash[hash[p1]].begin(), by_hash[hash[p1]].end(), p1));

            // swap s[p1][w1] and s[p2][w2]
            hash[p1] -= (s[p1][w1] - 'a' + 1) * modpow(HASH_BASE, w1, MOD9);
            hash[p1] += (s[p2][w2] - 'a' + 1) * modpow(HASH_BASE, w1, MOD9);
            hash[p1] = (hash[p1] % MOD9 + MOD9) % MOD9;

            hash[p2] -= (s[p2][w2] - 'a' + 1) * modpow(HASH_BASE, w2, MOD9);
            hash[p2] += (s[p1][w1] - 'a' + 1) * modpow(HASH_BASE, w2, MOD9);
            hash[p2] = (hash[p2] % MOD9 + MOD9) % MOD9;

            swap(s[p1][w1], s[p2][w2]);

            // add to by_hash
            by_hash[hash[p1]].push_back(p1);

            // update ans
            for (auto i : by_hash[hash[p1]]) {
                ans[i] = max(ans[i], (int)by_hash[hash[p1]].size());
            }
        }
        else {

            // remove from by_hash
            by_hash[hash[p1]].erase(find(by_hash[hash[p1]].begin(), by_hash[hash[p1]].end(), p1));
            by_hash[hash[p2]].erase(find(by_hash[hash[p2]].begin(), by_hash[hash[p2]].end(), p2));

            // swap s[p1][w1] and s[p2][w2]
            hash[p1] -= (s[p1][w1] - 'a' + 1) * modpow(HASH_BASE, w1, MOD9);
            hash[p1] += (s[p2][w2] - 'a' + 1) * modpow(HASH_BASE, w1, MOD9);
            hash[p1] = (hash[p1] % MOD9 + MOD9) % MOD9;

            hash[p2] -= (s[p2][w2] - 'a' + 1) * modpow(HASH_BASE, w2, MOD9);
            hash[p2] += (s[p1][w1] - 'a' + 1) * modpow(HASH_BASE, w2, MOD9);
            hash[p2] = (hash[p2] % MOD9 + MOD9) % MOD9;

            swap(s[p1][w1], s[p2][w2]);

            // add to by_hash
            by_hash[hash[p1]].push_back(p1);
            by_hash[hash[p2]].push_back(p2);

            // update ans
            for (auto i : by_hash[hash[p1]]) {
                ans[i] = max(ans[i], (int)by_hash[hash[p1]].size());
            }
            for (auto i : by_hash[hash[p2]]) {
                ans[i] = max(ans[i], (int)by_hash[hash[p2]].size());
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}