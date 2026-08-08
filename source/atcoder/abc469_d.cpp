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

    ll n, m;
    cin >> n >> m;

    vector<array<ll, 2>> ab(m);
    for (int i = 0; i < m; i++) {
        cin >> ab[i][0] >> ab[i][1];
        ab[i][0]--;
        ab[i][1]--;
    }
    sort(ab.begin(), ab.end());
    ab.erase(unique(ab.begin(), ab.end()), ab.end());
    m = ab.size();

    set<array<ll, 2>> ab_set(ab.begin(), ab.end());
    vector<ll> cnt(n);
    for (auto [a, b] : ab) {
        cnt[a]++;
        cnt[b]++;
    }

    map<ll, vector<ll>> by_cnt;
    for (int i = 0; i < n; i++) {
        by_cnt[cnt[i]].push_back(i);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int cur_cnt = cnt[i];
        for (auto elem : by_cnt[m - cur_cnt]) {
            if (elem <= i) {
                continue;
            }
            if (ab_set.count({i, elem}) == 0) {
                ans++;
            }
        }
        for (auto elem : by_cnt[m - cur_cnt + 1]) {
            if (elem <= i) {
                continue;
            }
            ans++;
        }
    }

    cout << ans;

    return 0;
}