// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_fail(const vector<int> &v) {
    int n = v.size();
    vector<int> fail(n, 0);
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && v[i] != v[j]) {
            j = fail[j - 1];
        }
        if (v[i] == v[j]) {
            fail[i] = j + 1;
            j++;
        }
    }

    return fail;
}

vector<int> kmp(const vector<int> &s, const vector<int> &t) {
    int n = s.size(), m = t.size();
    vector<int> fail = get_fail(t);
    vector<int> res;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j]) {
            j = fail[j - 1];
        }
        if (s[i] == t[j]) {
            if (j == m - 1) {
                res.push_back(i - m + 1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> dss(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        dss[i].resize(k - 1);
        vector<int> si(k);
        for (int j = 0; j < k; j++) {
            cin >> si[j];
        }
        for (int j = 0; j < k - 1; j++) {
            dss[i][j] = si[j + 1] - si[j];
        }
    }

    int l;
    cin >> l;
    vector<int> t(l);
    for (int i = 0; i < l; i++) {
        cin >> t[i];
    }
    vector<int> dt(l - 1);
    for (int i = 0; i < l - 1; i++) {
        dt[i] = t[i + 1] - t[i];
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        int match = kmp(dss[i], dt).size();
        if (match > 0) {
            ans.push_back(i + 1);
        }
    }

    if (ans.empty()) {
        cout << -1;
    } else {
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
    }

    return 0;
}