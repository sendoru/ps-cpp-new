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

    int n;
    cin >> n;
    vector<pii> edges(n);
    vector<int> colors_orig;

    for (int i = 0; i < n; i++) {
        cin >> edges[i].first;
        colors_orig.push_back(edges[i].first);
    }
    for (int i = 0; i < n; i++) {
        cin >> edges[i].second;
        colors_orig.push_back(edges[i].second);
    }

    sort(colors_orig.begin(), colors_orig.end());
    colors_orig.erase(unique(colors_orig.begin(), colors_orig.end()), colors_orig.end());
    for (int i = 0; i < n; i++) {
        edges[i].first = lower_bound(colors_orig.begin(), colors_orig.end(), edges[i].first) - colors_orig.begin();
        edges[i].second = lower_bound(colors_orig.begin(), colors_orig.end(), edges[i].second) - colors_orig.begin();
    }

    int color_cnt = colors_orig.size();

    vector<vector<int>> adj_list(color_cnt);

    for (auto [s, e] : edges) {
        adj_list[s].push_back(e);
        adj_list[e].push_back(s);
    }

    vector<int> cc_no(color_cnt, -1);
    vector<int> cc_size(color_cnt, 0);
    vector<int> edge_cnt(color_cnt, 0);
    int cur_cc = 0;

    for (int i = 0; i < color_cnt; i++) {
        if (cc_no[i] != -1) {
            continue;
        }
        queue<int> q;
        q.push(i);
        cc_no[i] = cur_cc;
        cc_size[cur_cc]++;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto next : adj_list[cur]) {
                if (cc_no[next] == -1) {
                    cc_no[next] = cur_cc;
                    cc_size[cur_cc]++;
                    q.push(next);
                }
            }
        }
        cur_cc++;
    }

    for (auto [s, e] : edges) {
        edge_cnt[cc_no[s]]++;
    }

    int ans = 0;
    for (int i = 0; i < cur_cc; i++) {
        if (cc_size[i] == edge_cnt[i] + 1) {
            ans += cc_size[i] - 1;
        } else {
            ans += cc_size[i];
        }
    }

    cout << ans << '\n';

    return 0;
}