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

    int n, q;
    cin >> n >> q;
    vector<int> par(n + q + 10, -1);
    vector<vector<pair<string, int>>> ss(n + q + 10);
    vector<int> last_update(n + q + 10, -1);

    int nxt_idx = n + 1;
    int server_idx = n;
    vector<int> idxs(n + 1);
    iota(idxs.begin(), idxs.end(), 0);

    for (int i = 0; i < q; i++) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int p;
            cin >> p;
            p--;
            idxs[p] = nxt_idx;
            par[idxs[p]] = server_idx;
            nxt_idx++;
            last_update[idxs[p]] = i;
        } else if (qt == 2) {
            int p;
            cin >> p;
            p--;
            string s;
            cin >> s;
            ss[idxs[p]].push_back({s, i});
            // last_update[idxs[p]] = i;
        } else {
            int p;
            cin >> p;
            p--;
            server_idx = nxt_idx;
            par[server_idx] = idxs[p];
            nxt_idx++;
            last_update[server_idx] = i;
        }
    }

    vector<string> ans;
    int cur = server_idx;
    while (cur != -1) {
        ans.push_back("");
        int prev = par[cur];
        if (prev == -1) {
            break;
        }
        for (const auto &s : ss[prev]) {
            if (s.second <= last_update[cur]) {
                ans.back() += s.first;
            }
        }
        cur = par[cur];
    }
    reverse(ans.begin(), ans.end());
    for (const auto &s : ans) {
        cout << s;
    }

    return 0;
}

// ladxfzzkfmirurptilun
// ladxfzzkfmirurptilun