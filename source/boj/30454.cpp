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

    int n, l;
    cin >> n >> l;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<string> ss(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            if (ss[i].empty() || ss[i].back() != s[i][j]) {
                ss[i] += s[i][j];
            }
        }
    }

    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        cnt[i] = count(ss[i].begin(), ss[i].end(), '1');
    }

    int ans1 = *max_element(cnt.begin(), cnt.end());
    int ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == ans1) {
            ans2++;
        }
    }

    cout << ans1 << " " << ans2;

    return 0;
}