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
    vector<array<ll, 2>> st(n);
    for (int i = 0; i < n; i++) {
        cin >> st[i][0] >> st[i][1];
    }
    sort(st.begin(), st.end());

    ll ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i < n; i++) {
        while (!pq.empty() && pq.top() <= st[i][0]) {
            pq.pop();
        }
        pq.push(st[i][1]);
        ans = max(ans, (ll)pq.size());
    }

    cout << ans;

    return 0;
}