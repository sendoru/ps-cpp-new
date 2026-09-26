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

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<ll> cw_min(n, 1e18), ccw_min(n, 1e18);
    // deque dp
    deque<pll> dq;
    ll offset = 0;
    // initialize deque
    ll cur_sum = 0;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.back().first >= cur_sum + b[i]) {
            dq.pop_back();
        }
        dq.push_back({cur_sum + b[i], i});
        cur_sum += a[i];
    }

    for (int i = 0; i < n; i++) {
        cw_min[i] = dq.front().first - offset;
        if (dq.front().second == i) {
            dq.pop_front();
        }
        while (!dq.empty() && dq.back().first >= cur_sum + offset + b[i]) {
            dq.pop_back();
        }
        dq.push_back({cur_sum + offset + b[i], i});
        offset += a[i];
    }

    // reversed direction
    reverse(a.begin(), a.end() - 1);
    reverse(b.begin(), b.end());
    dq.clear();
    offset = 0;
    cur_sum = 0;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.back().first >= cur_sum + b[i]) {
            dq.pop_back();
        }
        dq.push_back({cur_sum + b[i], i});
        cur_sum += a[i];
    }

    for (int i = 0; i < n; i++) {
        ccw_min[i] = dq.front().first - offset;
        if (dq.front().second == i) {
            dq.pop_front();
        }
        while (!dq.empty() && dq.back().first >= cur_sum + offset + b[i]) {
            dq.pop_back();
        }
        dq.push_back({cur_sum + offset + b[i], i});
        offset += a[i];
    }

    // reverse again to get the original order
    reverse(ccw_min.begin(), ccw_min.end());
    reverse(a.begin(), a.end() - 1);
    reverse(b.begin(), b.end());

    vector<ll> pf_sum(n + 1);
    for (int i = 0; i < n; i++) {
        pf_sum[i + 1] = pf_sum[i] + a[i];
    }

    while (q--) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        if (u > v) {
            swap(u, v);
        }

        if (v == n) {
            cout << min(cw_min[u], ccw_min[u]) << '\n';
            continue;
        }

        // walk clockwise from u to v, without passing through n
        ll direct_min = pf_sum[v] - pf_sum[u];
        // check counter-clockwise too
        direct_min = min(direct_min, pf_sum[n] - direct_min);
        ll u_center = min(cw_min[u], ccw_min[u]);
        ll v_center = min(cw_min[v], ccw_min[v]);
        cout << min(direct_min, u_center + v_center) << '\n';
    }

    return 0;
}

/*

73248844
265090269
226395315
244911927
150839817
7398452
90418863
68674005
226395315
198612707
68865651
265090269

73248844
265090269
226395315
244911927
150839817
7398452
90418863
68674005
226395315
198612707
68865651
265090269

*/