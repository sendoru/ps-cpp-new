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

    int h, w;
    cin >> h >> w;
    vector<string> ans(h, string(w, '.'));
    for (int i = 0; i < w; i++) {
        ans[0][i] = '#';
        ans[h - 1][i] = '#';
    }
    for (int i = 0; i < h; i++) {
        ans[i][0] = '#';
        ans[i][w - 1] = '#';
    }

    for (int i = 0; i < h; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}