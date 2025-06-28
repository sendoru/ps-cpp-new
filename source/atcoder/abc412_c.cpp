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
        int n;
        cin >> n;
        vector<int> s(n);
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        int ans = 2;
        int l = s[0], r = s.back();
        vector<int> s_new;
        for (int i = 0; i < n; i++) {
            if (s[i] >= l && s[i] <= r) {
                s_new.push_back(s[i]);
            }
        }

        sort(s_new.begin(), s_new.end());
        int cur = l;
        while (cur * 2 < r) {
            auto it = upper_bound(s_new.begin(), s_new.end(), cur * 2) - 1;
            if (*it == cur) {
                ans = -1;
                break;
            }
            ans++;
            cur = *it;
        }

        cout << ans << '\n';
    }

    return 0;
}