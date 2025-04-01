// #include "atcoder/all"
// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll HASH_BASE = 41;
const ll HASH_MOD = 1e9 + 13;

ll powers[200010];

ll hash_push_back(ll h, ll x)
{
    return (h * HASH_BASE + x) % HASH_MOD;
}
ll hash_pop_front(ll h, ll x, ll len)
{
    return (h - x * powers[len - 1] % HASH_MOD + HASH_MOD) % HASH_MOD;
}

unordered_map<ll, vector<int>> get_hash_indexs(const string &s, int len)
{
    unordered_map<ll, vector<int>> ret;
    if (len > s.size()) {
        return ret;
    }
    ll h = 0;
    for (int i = 0; i < len; i++) {
        h = hash_push_back(h, s[i]);
    }
    ret[h].push_back(0);
    for (int i = len; i < s.size(); i++) {
        h = hash_pop_front(h, s[i - len], len);
        h = hash_push_back(h, s[i]);
        ret[h].push_back(i - len + 1);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    powers[0] = 1;
    for (int i = 1; i < 200010; i++) {
        powers[i] = (powers[i - 1] * HASH_BASE) % HASH_MOD;
    }

    string s;
    cin >> s;
    int n = s.size();
    ll ans = 0;
    ll lo = 0, hi = n;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (mid == 0) {
            ans = max(ans, mid);
            lo = mid + 1;
            continue;
        }

        auto map_hashs = get_hash_indexs(s, mid);
        bool ok = false;
        for (auto [hash, indexs] : map_hashs) {
            if (indexs.back() - indexs.front() >= mid) {
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

    cout << (ans == 0 ? -1 : ans) << '\n';

    return 0;
}