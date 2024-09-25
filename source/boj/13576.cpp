// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_sa(string &s)
{
    int n = s.size();
    vector<int> sa(n);
    vector<int> group(n + 1);
    vector<int> new_group(n + 1);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        group[i] = s[i];
    }

    for (int diff = 1; diff < n; diff <<= 1) {
        auto cmp = [&](int i, int j) {
            if (group[i] == group[j]) {
                return group[i + diff] < group[j + diff];
            }
            return group[i] < group[j];
        };
        sort(sa.begin(), sa.end(), cmp);

        new_group[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            new_group[sa[i]] = new_group[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        group = new_group;
    }
    return sa;
}

vector<int> get_lcp_array(string &s, vector<int> &sa)
{
    int n = s.size();
    vector<int> lcp(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[sa[i]] = i;
    }

    for (int i = 0, k = 0; i < n; i++) {
        if (pos[i] == n - 1) {
            continue;
        }
        for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; k++) {
        }
        lcp[pos[i]] = k;
        if (k) {
            k--;
        }
    }
    return lcp;
}

vector<int> get_z_array(string &s)
{
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
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

    vector<int> sa = get_sa(s);
    vector<int> sa_inv(s.size());
    for (int i = 0; i < s.size(); i++) {
        sa_inv[sa[i]] = i;
    }
    vector<int> lcp = get_lcp_array(s, sa);
    vector<int> z = get_z_array(s);

    int n = s.size();
    // get all i s.t. s[i:] is prefix of s
    // and get the number of occurance of s[i:] in s for each i
    vector<int> idxs = {n};
    vector<int> occurs = {1};
    for (int i = 0; i < n; i++) {
        if (z[i] == n - i) {
            idxs.push_back(n - i);
            int sa_idx = sa_inv[i];
            // TODO fix
            occurs.push_back(sa_inv[0] - sa_idx + 1);
        }
    }

    reverse(idxs.begin(), idxs.end());
    reverse(occurs.begin(), occurs.end());

    cout << idxs.size() << '\n';
    for (int i = 0; i < idxs.size(); i++) {
        cout << idxs[i] << ' ' << occurs[i] << '\n';
    }

    return 0;
}