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

    vector<array<ll, 3>> vab(m);
    for (int i = 0; i < m; i++) {
        cin >> vab[i][0] >> vab[i][1] >> vab[i][2];
        vab[i][0]--;
    }

    vector<bool> visited(n, false);
    int visited_cnt = 0;
    vector<ll> prev_a(n, -1);
    ll a_sum = 0;
    ll ans = 4e18;
    ll prev_b = 0;
    sort(vab.begin(), vab.end(), [](const array<ll, 3> &a1, const array<ll, 3> &a2) {
        return a1[2] < a2[2];
    });

    for (auto [v, a, b] : vab) {
        if (!visited[v]) {
            visited[v] = true;
            prev_a[v] = a;
            visited_cnt++;
            a_sum += a;
        } else if (a < prev_a[v]) {
            a_sum -= prev_a[v];
            a_sum += a;
            prev_a[v] = a;
        }
        if (visited_cnt == n) {
            ans = min(ans, a_sum + b * k);
        }
        prev_b = b;
    }

    cout << ans << '\n';

    return 0;
}