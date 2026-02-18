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
    map<ll, ll> dist;
    dist[n] = 0;
    queue<ll> q;
    q.push(n);
    while (!q.empty()) {
        ll x = q.front();
        q.pop();
        if (x >= m) {
            continue;
        }
        if (dist.count(x * 2) == 0) {
            dist[x * 2] = dist[x] + 1;
            q.push(x * 2);
        }
        if (dist.count(10 * x + 1) == 0) {
            dist[10 * x + 1] = dist[x] + 1;
            q.push(10 * x + 1);
        }
    }

    if (dist.count(m) == 0) {
        cout << -1 << "\n";
    } else {
        cout << dist[m] + 1 << "\n";
    }

    return 0;
}