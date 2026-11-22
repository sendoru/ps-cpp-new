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
    vector<int> pids(n), ws(n);
    for (int i = 0; i < n; i++) {
        cin >> pids[i] >> ws[i];
    }

    vector<array<int, 3>> t_qid_pids(n);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < k; i++) {
        pq.push({0, i});
    }
    for (int i = 0; i < n; i++) {
        auto [t, qid] = pq.top();
        pq.pop();
        t_qid_pids[i] = {t + ws[i], -qid, pids[i]};
        pq.push({t + ws[i], qid});
    }
    sort(t_qid_pids.begin(), t_qid_pids.end());
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (ll)(i + 1) * t_qid_pids[i][2];
    }
    cout << ans;

    return 0;
}