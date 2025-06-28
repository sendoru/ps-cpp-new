// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<pii>> pick(int n) {
    vector<pii> cur;
    vector<int> used(n, 0);
    vector<vector<pii>> ret;
    function<void()> dfs = [&]() {
        if (cur.size() == n) {
            ret.push_back(cur);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (used[i] >= 2) {
                continue;
            }
            for (int j = i + 1; j < n; j++) {
                if (used[j] >= 2) {
                    continue;
                }
                if (!cur.empty() && cur.back() > make_pair(i, j)) {
                    continue; // Ensure pairs are in non-decreasing order
                }
                if (find(cur.begin(), cur.end(), make_pair(i, j)) != cur.end()) {
                    continue;
                }
                used[i]++;
                used[j]++;
                cur.push_back({i, j});
                dfs();
                cur.pop_back();
                used[i]--;
                used[j]--;
            }
        }
    };

    dfs();
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pii> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].x >> edges[i].y;
        edges[i].x--;
        edges[i].y--;
        if (edges[i].x > edges[i].y) {
            swap(edges[i].x, edges[i].y);
        }
    }

    vector<vector<pii>> all = pick(n);
    int ans = 1231231;
    for (auto &target : all) {
        int cur_ans = target.size() + m;
        for (auto &edge : edges) {
            if (find(target.begin(), target.end(), edge) != target.end()) {
                cur_ans -= 2;
            }
        }
        ans = min(ans, cur_ans);
    }

    cout << ans << '\n';

    return 0;
}