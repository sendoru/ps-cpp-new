// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll MOD19 = (ll)1e9 + 9;

ll modpow_3001[3333], modpow_4001[3333];

// vector<int> make_sa(vector<int> &v) {
//     int n = v.size();
//     vector<int> sa(n), ranks(n), tmp(n);
//     for (int i = 0; i < n; i++) {
//         sa[i] = i;
//         ranks[i] = v[i];
//     }
//     for (int k = 1; k < n; k *= 2) {
//         auto cmp = [&](int i, int j) {
//             if (ranks[i] != ranks[j])
//                 return ranks[i] < ranks[j];
//             int ri = (i + k < n) ? ranks[i + k] : -1;
//             int rj = (j + k < n) ? ranks[j + k] : -1;
//             return ri < rj;
//         };
//         sort(sa.begin(), sa.end(), cmp);
//         tmp[sa[0]] = 0;
//         for (int i = 1; i < n; i++) {
//             tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
//         }
//         ranks = tmp;
//     }
//     return sa;
// }

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
        if (e & 1)
            res = (res * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return res;
}

vector<int> merge(vector<int> &a, vector<int> &b) {
    if (a.empty()) {
        return b;
    }
    if (b.empty()) {
        return a;
    }
    int n = a.size(), m = b.size();
    vector<int> v;
    v.reserve(n + m);
    int a_idx = 0, b_idx = 0;
    vector<array<ll, 2>> a_hash(n), b_hash(m);
    a_hash[0] = {a[0], a[0]};
    b_hash[0] = {b[0], b[0]};
    for (int i = 1; i < n; i++) {
        a_hash[i] = {(a_hash[i - 1][0] * 3001 + a[i]) % MOD9, (a_hash[i - 1][1] * 4001 + a[i]) % MOD1};
    }
    for (int i = 1; i < m; i++) {
        b_hash[i] = {(b_hash[i - 1][0] * 3001 + b[i]) % MOD9, (b_hash[i - 1][1] * 4001 + b[i]) % MOD1};
    }
    while (a_idx < n || b_idx < m) {
        if (b_idx == m) {
            v.push_back(a[a_idx]);
            a_idx++;
        } else if (a_idx == n) {
            v.push_back(b[b_idx]);
            b_idx++;
        } else {
            if (a[a_idx] < b[b_idx]) {
                v.push_back(a[a_idx]);
                a_idx++;
            } else if (b[b_idx] < a[a_idx]) {
                v.push_back(b[b_idx]);
                b_idx++;
            } else {
                // use hashing and binary search to find the first different character
                int l = 1, r = min(n - a_idx, m - b_idx) + 1;
                while (l < r) {
                    int mid = (l + r) / 2;
                    auto a_sub_hash = a_hash[a_idx + mid - 1];
                    if (a_idx > 0) {
                        a_sub_hash[0] = (a_sub_hash[0] - (a_hash[a_idx - 1][0] * modpow_3001[mid] % MOD9) + MOD9) % MOD9;
                        a_sub_hash[1] = (a_sub_hash[1] - (a_hash[a_idx - 1][1] * modpow_4001[mid] % MOD1) + MOD1) % MOD1;
                    }
                    auto b_sub_hash = b_hash[b_idx + mid - 1];
                    if (b_idx > 0) {
                        b_sub_hash[0] = (b_sub_hash[0] - (b_hash[b_idx - 1][0] * modpow_3001[mid] % MOD9) + MOD9) % MOD9;
                        b_sub_hash[1] = (b_sub_hash[1] - (b_hash[b_idx - 1][1] * modpow_4001[mid] % MOD1) + MOD1) % MOD1;
                    }
                    if (a_sub_hash == b_sub_hash) {
                        l = mid + 1;
                    } else {
                        r = mid;
                    }
                }
                int common_len = l - 1;
                if (common_len == n - a_idx && common_len == m - b_idx) {
                    v.push_back(a[a_idx]);
                    a_idx++;
                } else if (common_len == n - a_idx) {
                    v.push_back(b[b_idx]);
                    b_idx++;
                } else if (common_len == m - b_idx) {
                    v.push_back(a[a_idx]);
                    a_idx++;
                } else {
                    if (a[a_idx + common_len] < b[b_idx + common_len]) {
                        v.push_back(a[a_idx]);
                        a_idx++;
                    } else {
                        v.push_back(b[b_idx]);
                        b_idx++;
                    }
                }
            }
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    modpow_3001[0] = 1;
    modpow_4001[0] = 1;
    for (int i = 1; i < 3333; i++) {
        modpow_3001[i] = (modpow_3001[i - 1] * 3001) % MOD9;
        modpow_4001[i] = (modpow_4001[i - 1] * 4001) % MOD1;
    }

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int k;
    cin >> k;

    // to find lexicographically smallest subsequence
    // dp[i][j]: the last index of the smallest subsequence of length j using first i elements
    vector<vector<int>> a_dp(n, vector<int>(n + 1, -1));
    a_dp[0][1] = 0;
    for (int i = 1; i < n; i++) {
        a_dp[i][1] = a_dp[i - 1][1];
        if (a[a_dp[i][1]] > a[i]) {
            a_dp[i][1] = i;
        }
    }
    for (int len = 2; len <= n; len++) {
        for (int i = len - 1; i < n; i++) {
            // try to use previous dp (a_dp[i - 1][len])
            if (a_dp[i - 1][len] != -1) {
                a_dp[i][len] = a_dp[i - 1][len];
            }
            // try to use a[i]
            if (a_dp[i - 1][len] == -1 || a[a_dp[i - 1][len]] > a[i] || a_dp[i - 1][len] == a_dp[i - 1][len - 1]) {
                a_dp[i][len] = i;
            }
        }
    }

    vector<vector<int>> b_dp(m, vector<int>(m + 1, -1));
    b_dp[0][1] = 0;
    for (int i = 1; i < m; i++) {
        b_dp[i][1] = b_dp[i - 1][1];
        if (b[b_dp[i][1]] > b[i]) {
            b_dp[i][1] = i;
        }
    }
    for (int len = 2; len <= m; len++) {
        for (int i = len - 1; i < m; i++) {
            if (b_dp[i - 1][len] != -1) {
                // try to use previous dp (b_dp[i - 1][len])
                b_dp[i][len] = b_dp[i - 1][len];
            }
            // try to use b[i]
            if (b_dp[i - 1][len] == -1 || b[b_dp[i - 1][len]] > b[i] || b_dp[i - 1][len] == b_dp[i - 1][len - 1]) {
                b_dp[i][len] = i;
            }
        }
    }

    vector<int> ans;
    for (int i = 1; i < k; i++) {
        int a_sub_len = i, b_sub_len = k - i;
        if (a_sub_len > n || b_sub_len > m) {
            continue;
        }
        vector<int> a_sub, b_sub;
        // reconstruct a_sub
        int idx = n - 1;
        while (a_sub_len > 0) {
            int a_idx = a_dp[idx][a_sub_len];
            a_sub.push_back(a[a_idx]);
            idx = a_idx - 1;
            a_sub_len--;
        }
        reverse(a_sub.begin(), a_sub.end());
        // reconstruct b_sub
        idx = m - 1;
        while (b_sub_len > 0) {
            int b_idx = b_dp[idx][b_sub_len];
            b_sub.push_back(b[b_idx]);
            idx = b_idx - 1;
            b_sub_len--;
        }
        reverse(b_sub.begin(), b_sub.end());
        vector<int> merged = merge(a_sub, b_sub);
        if (ans.empty() || merged < ans) {
            ans = merged;
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}