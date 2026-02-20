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

    ll n, m, k;
    cin >> n >> m >> k;
    vector<array<ll, 2>> cv(k);
    for (int i = 0; i < k; i++) {
        cin >> cv[i][1] >> cv[i][0];
    }
    sort(cv.begin(), cv.end());

    ll v_sum = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i < k; i++) {
        v_sum += cv[i][1];
        pq.push(cv[i][1]);
        if (pq.size() > n) {
            v_sum -= pq.top();
            pq.pop();
        }
        if (v_sum >= m && pq.size() == n) {
            cout << cv[i][0];
            return 0;
        }
    }

    cout << -1;

    return 0;
}