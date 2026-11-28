// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// ex:
// (()(())) == ((())())
int get_tree_hash(const string &s) {
    // 1. get matching parentheses
    int n = s.size();
    vector<int> match(n, -1);
    vector<int> st;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            st.push_back(i);
        } else {
            int j = st.back();
            st.pop_back();
            match[i] = j;
            match[j] = i;
        }
    }

    // 2. dfs
    function<ll(ll, ll)> dfs = [&](ll l, ll r) -> ll {
        if (l + 1 == r) {
            return 1;
        }

        vector<ll> child_hashes;
        for (ll i = l + 1; i < r; i++) {
            if (match[i] == -1) {
                continue;
            }
            ll j = match[i];
            child_hashes.push_back(dfs(i, j));
            i = j;
        }

        sort(child_hashes.begin(), child_hashes.end());
        ll res = 1;
        for (ll h : child_hashes) {
            res = (res * 31 + h) % MOD1;
        }
        return res;
    };

    return dfs(0, n - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s1, s2;
        cin >> s1 >> s2;
        s1 = "0" + s1 + "1";
        s2 = "0" + s2 + "1";
        int s1_hash = get_tree_hash(s1);
        int s2_hash = get_tree_hash(s2);
        cout << (s1_hash == s2_hash ? 1 : 0) << "\n";
    }

    return 0;
}