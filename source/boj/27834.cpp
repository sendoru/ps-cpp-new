// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const int MAX_N = 5;
int n, m;

map<tuple<int, vector<int>, ll>, ll> dp;

ll encode_touch(int i, int j) {
    return 1ll << ((i << 3) | j);
}

bool is_touching(ll touch, int i, int j) {
    return touch & encode_touch(i, j);
}

ll solve(int cur_row_no, ll touch, const vector<int> &pre_row_colors) {
    tuple<int, vector<int>, ll> state = {cur_row_no, pre_row_colors, touch};
    if (dp.count(state))
        return dp[state];
    ll &ret = dp[state];
    dp[state] = 0;
    if (cur_row_no == m) {
        return ret = 1;
    }

    for (int hori = 0; hori < (1 << n); hori++) {
        for (int vert = 0; vert < (1 << (n - 1)); vert++) {
            // [0, n): 이전 행, [n, 2 * n): 현재 행
            vector<vector<int>> adjm(2 * n, vector<int>(2 * n, 0));
            vector<int> color(2 * n, -1);
            for (int i = 0; i < 2 * n; i++) {
                adjm[i][i] = 1;
            }
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    if (pre_row_colors[u] == pre_row_colors[v]) {
                        adjm[u][v] = 1;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (!((hori >> i) & 1)) {
                    adjm[i][n + i] = 1;
                    adjm[n + i][i] = 1;
                }
            }
            for (int i = 0; i < n - 1; i++) {
                if (!((vert >> i) & 1)) {
                    adjm[n + i][n + i + 1] = 1;
                    adjm[n + i + 1][n + i] = 1;
                }
            }

            // floyd-warshall
            for (int k = 0; k < 2 * n; k++) {
                for (int i = 0; i < 2 * n; i++) {
                    for (int j = 0; j < 2 * n; j++) {
                        adjm[i][j] = adjm[i][j] | (adjm[i][k] & adjm[k][j]);
                    }
                }
            }

            // coloring
            int color_cnt = 0;
            for (int i = 0; i < 2 * n; i++) {
                int u = (i + n) % (2 * n);
                if (color[u] == -1) {
                    color[u] = color_cnt;
                    for (int v = 0; v < 2 * n; v++) {
                        if (adjm[u][v]) {
                            color[v] = color_cnt;
                        }
                    }
                    color_cnt++;
                }
            }

            // check validity
            bool ok = true;
            for (int i = 0; i < n - 1; i++) {
                if (pre_row_colors[i] != pre_row_colors[i + 1] && color[i] == color[i + 1]) {
                    ok = false;
                    break;
                }
            }
            for (int i = 0; i < n; i++) {
                if (((hori >> i) & 1) && color[i] == color[n + i]) {
                    ok = false;
                    break;
                }
            }
            for (int i = 0; i < n - 1; i++) {
                if (((vert >> i) & 1) && color[n + i] == color[n + i + 1]) {
                    ok = false;
                    break;
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (is_touching(touch, pre_row_colors[i], pre_row_colors[j]) && color[i] == color[j]) {
                        ok = false;
                        break;
                    }
                }
            }

            if (!ok) {
                continue;
            }

            vector<int> cur_row_colors(n);
            for (int i = 0; i < n; i++) {
                cur_row_colors[i] = color[n + i];
            }

            ll new_touch = 0;
            for (int i = 0; i < n - 1; i++) {
                if (cur_row_colors[i] != cur_row_colors[i + 1]) {
                    new_touch |= encode_touch(cur_row_colors[i], cur_row_colors[i + 1]);
                    new_touch |= encode_touch(cur_row_colors[i + 1], cur_row_colors[i]);
                }
            }

            int new_color_cnt = 0;
            for (int i = 0; i < n; i++) {
                new_color_cnt = max(new_color_cnt, cur_row_colors[i] + 1);
            }
            for (int i = 0; i < n; i++) {
                if (color[i] < new_color_cnt && color[i] != cur_row_colors[i]) {
                    new_touch |= encode_touch(color[i], cur_row_colors[i]);
                    new_touch |= encode_touch(cur_row_colors[i], color[i]);
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (is_touching(touch, pre_row_colors[i], pre_row_colors[j]) && color[i] < new_color_cnt && color[j] < new_color_cnt) {
                        new_touch |= encode_touch(color[i], color[j]);
                        new_touch |= encode_touch(color[j], color[i]);
                    }
                }
            }

            ret += solve(cur_row_no + 1, new_touch, cur_row_colors);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    ll ans = 0;

    for (int init_ver = 0; init_ver < (1 << (n - 1)); init_ver++) {
        vector<int> row(n);
        for (int i = 0; i < n - 1; i++) {
            row[i + 1] = row[i] + (1 - ((init_ver >> i) & 1));
        }
        ll touch = 0;
        for (int j = 0; j < row.back(); j++) {
            touch |= (encode_touch(j, j + 1) | encode_touch(j + 1, j));
        }
        ans += solve(1, touch, row);
    }

    cout << ans << "\n";

    return 0;
}