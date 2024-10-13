// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pii get_coord_after_op(int n, pii d, int op_cnt)
{
    switch (op_cnt % 4) {
    case 0:
        return d;
    case 1:
        return {d.second, n - 1 - d.first};
    case 2:
        return {n - 1 - d.first, n - 1 - d.second};
    case 3:
        return {n - 1 - d.second, d.first};
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> op_cnt(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // dist from boundary + 1
            int dist = min(i, n - 1 - i) + 1;
            dist = min(dist, min(j, n - 1 - j) + 1);
            op_cnt[i][j] = dist;
        }
    }

    vector<string> ans(n, string(n, ' '));

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            int op = op_cnt[x][y];
            auto [nx, ny] = get_coord_after_op(n, {x, y}, op);
            ans[nx][ny] = a[x][y];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}