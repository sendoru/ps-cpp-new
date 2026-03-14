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

    int t;
    cin >> t;
    while (t--) {
        ll n, k, l;
        cin >> n >> k >> l;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        priority_queue<ll> pq;
        for (int i = 0; i < n - 1; i++) {
            pq.push(a[i + 1] - a[i]);
        }
        ll left = a[0], right = l - a[n - 1];
        ll ans = 0, cur = 0;
        while (!pq.empty() && k > 0) {
            ans = max(ans, cur + max(left, right) + (k - 1) * (left + right));
            ll d = pq.top();
            pq.pop();
            cur += d / 2;
            left += d / 2;
            right += d / 2;
            k--;
        }
        if (k > 0) {
            ans = max(ans, cur + max(left, right) + (k - 1) * (left + right));
        } else {
            ans = max(ans, cur);
        }
        cout << ans << '\n';
    }

    return 0;
}