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
    map<char, int> cnt;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        cnt[s[0]]++;
    }
    string ans;
    for (auto &[c, cnt] : cnt) {
        if (cnt >= 5) {
            ans += c;
        }
    }
    if (ans.empty()) {
        cout << "PREDAJA";
    } else {
        sort(ans.begin(), ans.end());
        cout << ans;
    }

    return 0;
}