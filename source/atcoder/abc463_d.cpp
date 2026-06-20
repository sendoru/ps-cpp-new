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

    int n, k;
    cin >> n >> k;
    vector<array<ll, 2>> clothes(n);
    for (int i = 0; i < n; i++) {
        cin >> clothes[i][0] >> clothes[i][1];
    }
    sort(clothes.begin(), clothes.end());

    ll l = 1, r = 1e9 + 1;
    ll ans = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll cnt = 1;
        ll rightmost = clothes[0][1];
        for (int i = 1; i < n; i++) {
            if (rightmost + mid <= clothes[i][0]) {
                cnt++;
                rightmost = clothes[i][1];
            } else {
                rightmost = min(rightmost, clothes[i][1]);
            }
        }
        if (cnt >= k) {
            ans = max(ans, mid);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans;

    return 0;
}