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

    ll n;
    cin >> n;
    string s;
    cin >> s;

    array<vector<ll>, 3> cnt_prefix;
    for (int i = 0; i < 3; i++) {
        cnt_prefix[i].resize(n + 1);
    }
    for (int i = 0; i < n; i++) {
        cnt_prefix[s[i] - 'A'][i + 1]++;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= n; j++) {
            cnt_prefix[i][j] += cnt_prefix[i][j - 1];
        }
    }

    ll ans = n * (n + 1) / 2;
    for (auto [a, b] : vector<array<int, 2>>{{0, 1}, {1, 2}, {2, 0}}) {
        map<ll, ll> freq;
        for (int i = 0; i <= n; i++) {
            freq[cnt_prefix[a][i] - cnt_prefix[b][i]]++;
        }
        for (auto &[_, f] : freq) {
            ans -= f * (f - 1) / 2;
        }
    }

    map<array<ll, 2>, ll> freq;
    for (int i = 0; i <= n; i++) {
        array<ll, 2> key = {cnt_prefix[0][i] - cnt_prefix[1][i], cnt_prefix[1][i] - cnt_prefix[2][i]};
        freq[key]++;
    }
    for (auto &[_, f] : freq) {
        ans += f * (f - 1);
    }

    cout << ans;

    return 0;
}