// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Circle {
    ll x, y, r;
};

bool intersect(const Circle &a, const Circle &b) {
    ll dist_sq = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    ll r_sum_sq = (a.r + b.r) * (a.r + b.r);
    return dist_sq <= r_sum_sq;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<Circle> circles(n);
        for (int i = 0; i < n; i++) {
            cin >> circles[i].x >> circles[i].y >> circles[i].r;
        }

        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && intersect(circles[i], circles[j])) {
                    adj[i].push_back(j);
                }
            }
        }

        vector<bool> visited(n, false);
        int ans = 0;
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                ans++;
                visited[i] = true;
                q.push(i);
                while (!q.empty()) {
                    int cur = q.front();
                    q.pop();
                    for (int nxt : adj[cur]) {
                        if (!visited[nxt]) {
                            visited[nxt] = true;
                            q.push(nxt);
                        }
                    }
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}