// #include "atcoder/all"
#pragma GCC optimize("O3")
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
    vector<ll> cum(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> cum[2 * i];
    }
    for (int i = 0; i < n; i++) {
        cin >> cum[2 * i + 1];
        cum[2 * i + 1] *= -1;
    }

    ll min_cum = cum[0];
    for (int i = 1; i < 2 * n; i++) {
        cum[i] += cum[i - 1];
        min_cum = min(min_cum, cum[i]);
    }

    cout << count(cum.begin(), cum.end(), min_cum) << "\n";

    return 0;
}