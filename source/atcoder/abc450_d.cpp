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

    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    ll max_a = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        max_a = max(max_a, a[i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] += (max_a - a[i]) / k * k;
        pq.push(a[i]);
    }
    ll ans = 1e18;
    for (int i = 0; i < n + 1; i++) {
        ll x = pq.top();
        pq.pop();
        ans = min(ans, max_a - x);
        max_a = max(max_a, x + k);
        pq.push(x + k);
    }

    cout << ans;
    return 0;
}