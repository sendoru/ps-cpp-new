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

    vector<ll> cnt(1e7+1);
    for (ll i = 1; i <= 5000; i++) {
        for (ll j = i + 1; j <= 5000; j++) {
            ll val = i * i + j * j;
            if (val <= 1e7) {
                cnt[val]++;
            }
        }
    }

    ll n;
    cin >> n;

    vector<ll> ans;
    for (ll i = 1; i <= n; i++) {
        if (cnt[i] == 1) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << "\n";
    for (auto v : ans) {
        cout << v << " ";
    }


    return 0;
}