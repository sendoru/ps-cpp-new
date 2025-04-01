// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll HASH_BASE = 1000151;
const ll HASH_MOD = 1e9 + 7;

ll modpow(ll b, ll e, ll m)
{
    ll ret = 1;
    while (e > 0) {
        if (e & 1) {
            ret = (ret * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return ret;
}

ll hash_push_back(ll h, ll x)
{
    return (h * HASH_BASE + x) % HASH_MOD;
}
ll hash_pop_front(ll h, ll x, ll len)
{
    return (h - x * modpow(HASH_BASE, len - 1, HASH_MOD) % HASH_MOD + HASH_MOD) % HASH_MOD;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll lo = 0, hi = n - 1;
    ll ans = 0;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        map<ll, int> cnt;
        auto it_l = a.begin(), it_r = a.begin();
        // make first window
        ll h = 0;
        for (int i = 0; i < mid; i++) {
            h = hash_push_back(h, a[i]);
            it_r++;
        }
        cnt[h]++;
        while (it_r != a.end()) {
            h = hash_pop_front(h, *it_l, mid);
            h = hash_push_back(h, *it_r);
            it_l++;
            it_r++;
            cnt[h]++;
        }
        bool ok = false;
        for (auto [hash, v] : cnt) {
            if (v >= k) {
                ok = true;
                break;
            }
        }
        if (ok) {
            ans = max(ans, mid);
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << ans << '\n';

    return 0;
}