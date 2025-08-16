// #include "atcoder/all"
// this code is doomed
#pragma GCC optimize("Ofast")
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

    int n, l;
    cin >> n >> l;
    vector<string> ss(n);
    for (int i = 0; i < n; i++) {
        cin >> ss[i];
    }

    vector<string> prefixes;
    for (int i = 0; i < n; i++) {
        string cur = "";
        for (int j = 0; j < ss[i].size(); j++) {
            cur += ss[i][j];
            prefixes.push_back(cur);
        }
    }
    vector<string> rev_prefixes = prefixes;
    for (auto &s : rev_prefixes) {
        reverse(s.begin(), s.end());
    }

    sort(prefixes.begin(), prefixes.end(), [](const string &a, const string &b) {
        if (a.size() == b.size()) {
            return a < b;
        }
        return a.size() > b.size();
    });

    // count of length-l strings that contains all of ss as (consecutive) substrings, on mod MOD9

    vector<unordered_map<string, ll>> dp(vector<unordered_map<string, ll>>(1 << n));
    dp[0][""] = 1;

    for (int i = 0; i < l; i++) {
        vector<unordered_map<string, ll>> n_dp(vector<unordered_map<string, ll>>(1 << n));
        for (int mask = 0; mask < (1 << n); mask++) {
            for (const auto &[rev_prefix, count] : dp[mask]) {
                for (char c = 'a'; c <= 'z'; c++) {
                    string n_rev_prefix = c + rev_prefix;
                    while (!n_rev_prefix.empty()) {
                        auto it = find(rev_prefixes.begin(), rev_prefixes.end(), n_rev_prefix);
                        if (it != rev_prefixes.end()) {
                            break;
                        }
                        n_rev_prefix.pop_back();
                    }
                    int n_mask = mask;
                    string n_prefix = n_rev_prefix;
                    reverse(n_prefix.begin(), n_prefix.end());
                    for (int j = 0; j < n; j++) {
                        if (n_prefix == ss[j]) {
                            n_mask |= (1 << j);
                        }
                    }
                    n_dp[n_mask][n_rev_prefix] = (n_dp[n_mask][n_rev_prefix] + count) % MOD9;
                }
            }
        }
        dp = n_dp;
    }

    ll ans = 0;
    for (const auto &[prefix, count] : dp[(1 << n) - 1]) {
        ans = (ans + count) % MOD9;
    }

    cout << ans << '\n';

    return 0;
}