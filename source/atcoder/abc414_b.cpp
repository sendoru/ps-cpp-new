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
    vector<char> c(n);
    vector<ll> l(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> l[i];
    }

    ll l_sum = 0;
    for (ll length : l) {
        l_sum += length;
        if (l_sum > 100) {
            cout << "Too Long";
            return 0;
        }
    }
    string ans = "";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l[i]; j++) {
            ans += c[i];
        }
    }
    cout << ans;

    return 0;
}