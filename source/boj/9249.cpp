// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> get_substr_hash(const string &s, ll base, ll mod, ll len) {
    int n = s.size();
    vector<ll> ret;
    if (len > n) {
        return ret;
    }
    ll hash = 0, power = 1;
    for (int i = 0; i < len; i++) {
        hash = (hash * base + s[i]) % mod;
        if (i < len - 1) {
            power = (power * base) % mod;
        }
    }

    ret.push_back(hash);
    for (int i = len; i < n; i++) {
        // pop
        hash = (hash - s[i - len] * power % mod + mod) % mod;
        // push
        hash = (hash * base + s[i]) % mod;
        ret.push_back(hash);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const ll B1 = 131, B2 = 137;
    const ll M1 = (ll)1e9 + 7, M2 = 998244353;

    string s1, s2;
    cin >> s1 >> s2;
    int lo = 0, hi = min(s1.size(), s2.size());
    int max_len = 0, pos = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        vector<pll> s1_hash, s2_hash;
        auto h1 = get_substr_hash(s1, B1, M1, mid);
        auto h2 = get_substr_hash(s1, B2, M2, mid);
        for (int i = 0; i < h1.size(); i++) {
            s1_hash.push_back({h1[i], h2[i]});
        }
        sort(s1_hash.begin(), s1_hash.end());
        h1 = get_substr_hash(s2, B1, M1, mid);
        h2 = get_substr_hash(s2, B2, M2, mid);
        for (int i = 0; i < h1.size(); i++) {
            s2_hash.push_back({h1[i], h2[i]});
        }
        bool found = false;
        int cur_pos = -1;
        for (int i = 0; i < s2_hash.size(); i++) {
            if (binary_search(s1_hash.begin(), s1_hash.end(), s2_hash[i])) {
                found = true;
                cur_pos = i;
                break;
            }
        }

        if (found) {
            max_len = mid;
            pos = cur_pos;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << max_len << '\n';
    if (max_len > 0) {
        cout << s2.substr(pos, max_len) << '\n';
    }

    return 0;
}