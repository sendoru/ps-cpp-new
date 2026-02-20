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
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        pq.push(x);
    }

    ll ans = 0;
    while (pq.size() >= 2) {
        ll x = pq.top();
        pq.pop();
        ll y = pq.top();
        pq.pop();
        ans += x + y;
        pq.push(x + y);
    }

    cout << ans;

    return 0;
}