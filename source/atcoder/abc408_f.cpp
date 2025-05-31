#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
using namespace atcoder;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int e() {
    return -MOD9;
}

int max_int(int a, int b) {
    return max(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, d, r;
    cin >> n >> d >> r;
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        h[i]--;
    }

    vector<int> h_inv(n);
    for (int i = 0; i < n; i++) {
        h_inv[h[i]] = i;
    }

    segtree<int, max_int, e> seg(n);
    vector<int> dp(n, 0);
    queue<int> q;
    for (auto idx : h_inv) {
        int left = max(idx - r, 0);
        int right = min(idx + r, n - 1);
        int mx = seg.prod(left, right + 1);
        dp[idx] = max(dp[idx], mx + 1);
        q.push(idx);
        if (q.size() >= d) {
            int front = q.front();
            q.pop();
            seg.set(front, dp[front]);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << '\n';

    return 0;
}