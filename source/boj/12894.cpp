// #include "atcoder/all"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

string s1, s2;
vector<ll> h1, h2;
vector<ll> modpows;

ll subhash(vector<ll> &h, int l, int r) {
    if (l == 0) {
        return h[r - 1];
    } else {
        ll res = h[r - 1] - (h[l - 1] * modpows[r - l]) % MOD9;
        if (res < 0) {
            res += MOD9;
        }
        return res;
    }
}

bool check(int l1, int r1, int l2, int r2) {
    int n = r1 - l1;
    if (n == 1 && h1[l1] == h2[l2]) {
        return true;
    }
    if (n % 2 == 0) {
        int mid1 = l1 + n / 2;
        int mid2 = l2 + n / 2;
        if ((check(l1, mid1, l2, mid2) && check(mid1, r1, mid2, r2)) ||
            (check(l1, mid1, mid2, r2) && check(mid1, r1, l2, mid2))) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s1 >> s2;
    h1.resize(s1.size());
    h2.resize(s2.size());
    modpows.resize(max(s1.size(), s2.size()) + 1);
    modpows[0] = 1;
    for (int i = 1; i < modpows.size(); i++) {
        modpows[i] = (modpows[i - 1] * 131) % MOD9;
    }

    h1[0] = s1[0];
    for (int i = 1; i < s1.size(); i++) {
        h1[i] = h1[i - 1] * 131 + s1[i];
        h1[i] %= MOD9;
    }
    h2[0] = s2[0];
    for (int i = 1; i < s2.size(); i++) {
        h2[i] = h2[i - 1] * 131 + s2[i];
        h2[i] %= MOD9;
    }

    ll chunk_size = h1.size();
    while (chunk_size % 2 == 0) {
        chunk_size /= 2;
    }

    vector<ll> new_h1, new_h2;
    for (int i = 0; i < h1.size(); i += chunk_size) {
        new_h1.push_back(subhash(h1, i, i + chunk_size));
    }
    for (int i = 0; i < h2.size(); i += chunk_size) {
        new_h2.push_back(subhash(h2, i, i + chunk_size));
    }
    h1 = new_h1;
    h2 = new_h2;

    if (check(0, h1.size(), 0, h2.size())) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}