// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int diff_cnt(string &s, string &t) {
    if (s.size() != t.size()) {
        return -1;
    }
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != t[i]) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> s(n), t(m);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> t[i];
    }

    vector<int> ans(n);
    for (int i = 0; i < m; i++) {
        bool done = false;
        for (int j = 0; j < n; j++) {
            if (s[j] == t[i]) {
                ans[j]++;
                done = true;
                break;
            }
        }
        if (done) {
            continue;
        }
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (diff_cnt(s[j], t[i]) == 1) {
                cnt++;
            }
        }
        if (cnt == 1) {
            for (int j = 0; j < n; j++) {
                if (diff_cnt(s[j], t[i]) == 1) {
                    ans[j]++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}