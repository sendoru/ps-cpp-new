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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    if (n % 2 == 0) {
        ll ans = 0;
        for (int i = 0; i < n / 2 - 1; i++) {
            ans += 2 * (a[n - 1 - i] - a[i]);
        }
        ans += a[n / 2] - a[n / 2 - 1];
        cout << ans;
    } else {
        ll ans1 = 0, ans2 = 0;
        // 1. 중앙값을 위로 넣기
        for (int i = 0; i < n / 2; i++) {
            ans1 -= 2 * a[i];
        }
        ans1 += a[n / 2];
        ans1 += a[n / 2 + 1];
        for (int i = n / 2 + 2; i < n; i++) {
            ans1 += 2 * a[i];
        }

        // 2. 중앙값을 아래로 넣기
        for (int i = 0; i < n / 2 - 1; i++) {
            ans2 -= 2 * a[i];
        }
        ans2 -= a[n / 2 - 1];
        ans2 -= a[n / 2];
        for (int i = n / 2 + 1; i < n; i++) {
            ans2 += 2 * a[i];
        }

        cout << max(ans1, ans2);
    }

    return 0;
}