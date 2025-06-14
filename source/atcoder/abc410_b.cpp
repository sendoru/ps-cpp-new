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
    vector<int> x(q + 1);
    for (int i = 1; i <= q; i++) {
        cin >> x[i];
    }

    vector<int> ans(q + 1, 0);
    vector<int> cnt(n + 1, 0);
    for (int i = 1; i <= q; i++) {
        if (x[i] != 0) {
            ans[i] = x[i];
            cnt[x[i]]++;
        } else {
            auto iter = min_element(cnt.begin() + 1, cnt.end());
            ans[i] = iter - cnt.begin();
            cnt[ans[i]]++;
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}

// 4 6 1 3 4 2 6 5 2 3 1 3 2 5 1 3 5 4 2 6
// 4 6 1 3 4 2 6 5 2 3 1 3 2 5 1 3 5 4 2 6