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

    int n, q;
    cin >> n >> q;
    vector<int> k(q);
    for (int i = 0; i < q; i++) {
        cin >> k[i];
    }

    vector<int> res(n);
    iota(res.begin(), res.end(), 1);
    for (int i = 0; i < q; i++) {
        reverse(res.begin(), res.begin() + k[i]);
        for (int j = 0; j < k[i]; j++) {
            res[j] *= -1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << '\n';
    }

    return 0;
}