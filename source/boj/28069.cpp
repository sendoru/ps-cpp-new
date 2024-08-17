#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> dist(n + 1, INT32_MAX);
    dist[0] = 0;
    queue<pii> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto [cur, d] = q.front();
        q.pop();
        if (cur == n) {
            dist[n] = d;
            break;
        }
        int nxt = cur + 1;
        if (nxt <= n && dist[nxt] > d + 1) {
            dist[nxt] = d + 1;
            q.push({nxt, d + 1});
        }
        nxt = cur + (cur / 2);
        if (nxt <= n && dist[nxt] > d + 1) {
            dist[nxt] = d + 1;
            q.push({nxt, d + 1});
        }
    }

    if (dist[n] <= k) {
        cout << "minigimbob";
    } else {
        cout << "water";
    }

    return 0;
}