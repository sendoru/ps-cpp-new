// #include "atcoder/all"
#pragma GCC optimize("O3")
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
    vector<array<ll, 2>> dist(500'001, {-1, -1});
    dist[n][0] = 0;
    queue<array<ll, 2>> q;
    q.push({n, 0});
    while (!q.empty()) {
        auto [pos, parity] = q.front();
        q.pop();

        for (int npos : {pos - 1, pos + 1, pos * 2}) {
            if (npos < 0 || npos > 500000) {
                continue;
            }
            if (dist[npos][1 - parity] == -1) {
                dist[npos][1 - parity] = dist[pos][parity] + 1;
                q.push({npos, 1 - parity});
            }
        }
    }

    ll ans = 1e9;
    ll t = 0;
    while (k <= 500000) {
        if (dist[k][t % 2] != -1 && dist[k][t % 2] <= t) {
            ans = min(ans, t);
        }
        t++;
        k += t;
    }

    if (ans == 1e9) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}