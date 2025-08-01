// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve_pq(vector<pll> &th) {
    ll n = th.size();
    ll ans = 0, t_sum = 0;
    priority_queue<ll> pq;
    for (int i = 0; i < n; i++) {
        if (th[i].first > th[i].second) {
            continue;
        }
        if (t_sum + th[i].first <= th[i].second) {
            pq.push(th[i].first);
            t_sum += th[i].first;
        } else if (pq.top() > th[i].first) {
            t_sum -= pq.top();
            pq.pop();
            pq.push(th[i].first);
            t_sum += th[i].first;
        }
        ans = max(ans, (ll)pq.size());
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pll> th(n);
    for (int i = 0; i < n; i++) {
        cin >> th[i].first >> th[i].second;
    }
    sort(th.begin(), th.end(), [](auto &x, auto &y) {
        return x.second < y.second;
    });

    cout << solve_pq(th);

    return 0;
}