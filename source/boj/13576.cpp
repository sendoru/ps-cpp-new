// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_suffix_array(string &s)
{
    int n = s.size();
    vector<int> sa(n), group(n + 1), new_group(n + 1);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        group[i] = s[i];
    }

    group[n] = -1;
    auto cmp = [&](int i, int j) {
        if (group[i] == group[j]) {
            return group[i + 1] < group[j + 1];
        }
        else {
            return group[i] < group[j];
        }
    };

    for (int d = 1; d < n; d <<= 1) {
        sort(sa.begin(), sa.end(), cmp);
        new_group[sa[0]] = 0;
        new_group[n] = -1;
        for (int i = 1; i < n; i++) {
            if (cmp(sa[i - 1], sa[i])) {
                new_group[sa[i]] = new_group[sa[i - 1]] + 1;
            }
            else {
                new_group[sa[i]] = new_group[sa[i - 1]];
            }
        }
        group = new_group;
    }

    return sa;
}

vector<int> get_lcp_array(string &s, vector<int> &sa)
{
    int n = s.size();
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[sa[i]] = i;
    }

    vector<int> lcp(n, 0);
    for (int i = 0, k = 0; i < n; i++, k = max(k - 1, 0)) {
        if (pos[i] == n - 1) {
            continue;
        }

        for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; k++) {
        }
        lcp[pos[i]] = k;
    }

    return lcp;
}

vector<int> get_z_array(string &s)
{
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, left = 0, right = 0; i < n; i++) {
        if (i <= right) {
            z[i] = min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    auto z = get_z_array(s);
    auto tmp = z;
    tmp[0] = s.size();
    sort(tmp.begin(), tmp.end());
    vector<pii> ans;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (z[i] == s.size() - i) {
            ans.push_back({z[i], tmp.end() - lower_bound(tmp.begin(), tmp.end(), z[i])});
        }
    }

    ans.push_back({s.size(), 1});

    cout << ans.size() << '\n';
    for (auto &p : ans) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}