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

    ll n;
    cin >> n;
    vector<array<ll, 2>> pd(n);
    // same start, different deadline schedule
    // p: weight, d: deadline
    for (int i = 0; i < n; i++) {
        cin >> pd[i][0] >> pd[i][1];
    }
    sort(pd.begin(), pd.end(), [](const array<ll, 2> &a, const array<ll, 2> &b) {
        if (a[1] == b[1]) {
            return a[0] > b[0];
        } else {
            return a[1] < b[1];
        }
    });

    ll ans = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i < n; i++) {
        pq.push(pd[i][0]);
        // only N schedules can be done during N days
        if (pq.size() > pd[i][1]) {
            pq.pop();
        }
    }
    while (!pq.empty()) {
        ans += pq.top();
        pq.pop();
    }
    cout << ans;
    return 0;
}