// #include "atcoder/all"
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

    ll q;
    cin >> q;
    string s, t;
    cin >> s >> t;

    vector<ll> idxs;
    for (int i = 0; i < s.size(); i++) {
        bool ok = true;
        for (int j = 0; j < t.size(); j++) {
            if (i + j >= s.size() || s[i + j] != t[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            idxs.push_back(i);
        }
    }

    while(q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        auto first_idx_it = lower_bound(idxs.begin(), idxs.end(), l);
        if (first_idx_it != idxs.end() && *first_idx_it + t.size() - 1 <= r) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }

    return 0;
}