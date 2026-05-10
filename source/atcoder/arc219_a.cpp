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

    ll n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (ll i = 0; i < n; i++) {
        cin >> s[i];
    }

    if (n == (1 << m)) {
        cout << "No";
        return 0;
    }

    vector<bool> done(n);
    string ans;
    for (ll i = 0; i < m; i++) {
        array<int, 2> cnt = {0, 0};
        for (int j = 0; j < n; j++) {
            if (!done[j]) {
                cnt[s[j][i] - '0']++;
            }
        }
        if (cnt[0] >= cnt[1]) {
            ans += '0';
            for (int j = 0; j < n; j++) {
                if (!done[j] && s[j][i] == '0') {
                    done[j] = true;
                }
            }
        } else {
            ans += '1';
            for (int j = 0; j < n; j++) {
                if (!done[j] && s[j][i] == '1') {
                    done[j] = true;
                }
            }
        }
    }

    cout << "Yes\n"
         << ans;

    return 0;
}