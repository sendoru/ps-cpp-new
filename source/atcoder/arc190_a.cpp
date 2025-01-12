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
    vector<vector<ll>> segs(m, vector<ll>(3));
    for (int i = 0; i < m; i++) {
        cin >> segs[i][0] >> segs[i][1];
        segs[i][0]--;
        segs[i][1]--;
        segs[i][2] = i;
    }

    // cost ==  1 iff there exists segs[i] == {0, n - 1}
    for (int i = 0; i < m; i++) {
        if (segs[i][0] == 0 && segs[i][1] == n - 1) {
            cout << 1 << endl;
            for (int j = 0; j < m; j++) {
                if (j == i) {
                    cout << 1 << ' ';
                } else {
                    cout << 0 << ' ';
                }
            }
            return 0;
        }
    }

    sort(segs.begin(), segs.end(), [](const vector<ll> &a, const vector<ll> &b) {
        if (a[0] != b[0]) {
            return a[0] < b[0];
        }
        return a[1] > b[1];
    });

    // cost == 2 exists if {i, j} satisfies one of the following conditions:
    // 1. segs[i] == {0, x} and segs[j] == {y, n - 1}
    // 2. segs[i] contains segs[j], that means segs[i].first <= segs[j].first and segs[j].second <= segs[i].second
    // 3. segs[i] and segs[j] are disjoint

    // deal cond 3 first
    int righmost_index = segs.back()[2];
    for (int i = 0; i < m; i++) {
        if (segs[i][1] < segs.back()[0]) {
            cout << 2 << endl;
            vector<int> ans(m);
            for (int j = 0; j < m; j++) {
                if (j == i || j == m - 1) {
                    ans[segs[j][2]] = 2;
                } else {
                    ans[segs[j][2]] = 0;
                }
            }
            for (int j = 0; j < m; j++) {
                cout << ans[j] << ' ';
            }
            return 0;
        }
    }

    bool has_zero = segs[0][0] == 0;
    int cost = MOD1;
    int max_r = segs[0][1];
    int max_r_idx = segs[0][2];
    vector<int> ans(m);
    for (int i = 1; i < m; i++) {
        // cond 1
        if (segs[i][1] == n - 1 && has_zero) {
            cost = 2;
            fill(ans.begin(), ans.end(), 0);
            if (segs[0][1] >= segs[i][0]) {
                ans[segs[0][2]] = ans[segs[i][2]] = 1;
            } else {
                ans[segs[0][2]] = ans[segs[i][2]] = 2;
            }
            break;
        }
        // cond 2, where segs[i - 1] contains segs[i]
        if (segs[i][1] <= max_r) {
            cost = 2;
            fill(ans.begin(), ans.end(), 0);
            ans[segs[i][2]] = 2;
            ans[max_r_idx] = 1;
            break;
        }
        if (i == 2) {
            cost = 3;
            fill(ans.begin(), ans.end(), 0);
            ans[segs[0][2]] = ans[segs[2][2]] = 1;
            ans[segs[1][2]] = 2;
        }
        if (max_r < segs[i][1]) {
            max_r = segs[i][1];
            max_r_idx = segs[i][2];
        }
    }

    if (cost == MOD1) {
        cout << -1;
    } else {
        cout << cost << endl;
        for (int i = 0; i < m; i++) {
            cout << ans[i] << ' ';
        }
    }

    return 0;
}