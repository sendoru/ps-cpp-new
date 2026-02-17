// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> d;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int len = 1; len <= 10; len++) {
        for (int i = 0; i < (1 << len); i++) {
            ll x = 0;
            for (int j = 0; j < len; j++) {
                if (i & (1 << j)) {
                    x = x * 10 + 7;
                } else {
                    x = x * 10 + 4;
                }
            }
            d.push_back(x);
        }
    }

    sort(d.begin(), d.end());

    int n;
    cin >> n;
    vector<int> pre(n + 1, -1);
    queue<int> q;
    pre[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (ll x : d) {
            ll v = (u + x);
            if (v > n) {
                break;
            }
            if (pre[v] == -1) {
                pre[v] = u;
                q.push(v);
            }
        }
    }
    if (pre[n] == -1) {
        cout << -1;
        return 0;
    }
    vector<int> ans;
    while (n > 0) {
        ans.push_back(n - pre[n]);
        n = pre[n];
    }
    sort(ans.begin(), ans.end());
    for (int x : ans) {
        cout << x << ' ';
    }
    return 0;
}