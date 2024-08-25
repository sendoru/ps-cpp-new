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

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            a[i][j] -= a[i].back();
        }
    }

    vector<int> rev_ans;

    for (int i = 0; i < n - 1; i++) {
        vector<pii> b;
        for (int j = 0; j < m; j++) {
            b.push_back({a[j][i], j});
        }

        sort(b.begin(), b.end(), greater<>());
        int cur_cnt = 0;
        vector<int> cur;
        for (int j = 0; j < m; j++) {
            cur_cnt += b[j].first;
            if (cur_cnt < 0) {
                break;
            }
            cur.push_back(b[j].second);
        }
        if (cur.size() > rev_ans.size()) {
            rev_ans = cur;
        }
    }

    cout << m - rev_ans.size() << '\n';
    vector<bool> is_rev(m);
    for (int i : rev_ans) {
        is_rev[i] = true;
    }
    for (int i = 0; i < m; i++) {
        if (!is_rev[i]) {
            cout << i + 1 << ' ';
        }
    }

    return 0;
}