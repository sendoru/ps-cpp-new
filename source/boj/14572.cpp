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

    ll n, k, d;
    cin >> n >> k >> d;

    vector<pii> infos(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m >> infos[i].first;
        for (int j = 0; j < m; j++) {
            int skill;
            cin >> skill;
            infos[i].second |= (1 << (skill - 1));
        }
    }

    sort(infos.begin(), infos.end());

    vector<int> counts(k, 0);
    ll ans = 0;
    auto iter_l = infos.begin(), iter_r = infos.begin();
    while (iter_l != infos.end()) {
        while (iter_r != infos.end() && iter_r->first - iter_l->first <= d) {
            for (int i = 0; i < k; i++) {
                if (iter_r->second & (1 << i)) {
                    counts[i]++;
                }
            }
            iter_r++;
        }
        ll or_popcnt = 0, and_popcnt = 0;
        for (int i = 0; i < k; i++) {
            if (counts[i] > 0) {
                or_popcnt++;
            }
            if (counts[i] == iter_r - iter_l) {
                and_popcnt++;
            }
        }
        ans = max(ans, (or_popcnt - and_popcnt) * (ll)(iter_r - iter_l));
        for (int i = 0; i < k; i++) {
            if (iter_l->second & (1 << i)) {
                counts[i]--;
            }
        }
        iter_l++;
    }

    cout << ans << '\n';

    return 0;
}