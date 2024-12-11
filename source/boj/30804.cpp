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

    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<int> cnts(10);
    int l = 0, r = 0, cur_cnt = 1, ans = 0;
    cnts[s[0]]++;
    while (l < n && r < n) {
        if (cur_cnt <= 2) {
            ans = max(ans, r - l + 1);
            r++;
            if (r < n) {
                if (cnts[s[r]] == 0) {
                    cur_cnt++;
                }
                cnts[s[r]]++;
            }
        } else {
            cnts[s[l]]--;
            if (cnts[s[l]] == 0) {
                cur_cnt--;
            }
            l++;
        }
    }

    cout << ans << '\n';

    return 0;
}