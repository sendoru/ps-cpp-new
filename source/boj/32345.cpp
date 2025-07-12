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

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();

        vector<int> vowel_idx;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
                vowel_idx.push_back(i);
            }
        }

        if (vowel_idx.size() == 0) {
            cout << "-1\n";
            continue;
        }

        ll ans = 1;
        for (int i = 0; i < vowel_idx.size() - 1; i++) {
            ll dist = vowel_idx[i + 1] - vowel_idx[i];
            ans = (ans * dist) % MOD1;
        }

        cout << ans << "\n";
    }

    return 0;
}