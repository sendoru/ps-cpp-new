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
    vector<int> pre(200'001, -1);
    pre[n] = n;
    queue<int> q;
    q.push(n);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (x - 1 >= 0 && pre[x - 1] == -1) {
            pre[x - 1] = x;
            q.push(x - 1);
        }
        if (x + 1 <= pre.size() && pre[x + 1] == -1) {
            pre[x + 1] = x;
            q.push(x + 1);
        }
        if (x * 2 <= pre.size() && pre[x * 2] == -1) {
            pre[x * 2] = x;
            q.push(x * 2);
        }
    }

    vector<int> ans;
    int x = k;
    while (!(pre[x] == x)) {
        ans.push_back(x);
        x = pre[x];
    }
    ans.push_back(n);
    reverse(ans.begin(), ans.end());
    cout << ans.size() - 1 << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}