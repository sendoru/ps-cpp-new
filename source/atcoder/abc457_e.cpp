#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int op_min(int a, int b) {
    return min(a, b);
}

int e_min() {
    return 1e9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> s_to_t(n + 1), t_to_s(n + 1);
    vector<int> min_t(n + 1, 1e9), second_min_t(n + 1, 1e9);
    for (int i = 0; i < m; i++) {
        int s, t;
        cin >> s >> t;
        s_to_t[s].push_back(t);
        t_to_s[t].push_back(s);
    }
    for (int i = 1; i <= n; i++) {
        sort(s_to_t[i].begin(), s_to_t[i].end());
        sort(t_to_s[i].begin(), t_to_s[i].end());
        if (s_to_t[i].size() >= 1) {
            min_t[i] = s_to_t[i][0];
        }
        if (s_to_t[i].size() >= 2) {
            second_min_t[i] = s_to_t[i][1];
        }
    }

    atcoder::segtree<int, op_min, e_min> seg(min_t);

    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;

        auto s_to_t_it = upper_bound(s_to_t[s].begin(), s_to_t[s].end(), t);
        if (s_to_t_it == s_to_t[s].begin()) {
            cout << "No\n";
            continue;
        }
        s_to_t_it--;
        // case 1: single cloth covers all from s to t
        // need to find another one that is completely included in [s, t]
        if (*s_to_t_it == t) {
            // exclude currently selected cloth
            int cur_min_t = seg.prod(s + 1, t + 1);
            if (*s_to_t_it != min_t[s]) {
                cur_min_t = min(cur_min_t, min_t[s]);
            } else {
                cur_min_t = min(cur_min_t, second_min_t[s]);
            }
            if (cur_min_t <= t) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
        // case 2: there exists a cloth that stars from s but ends before t
        // need to find another one
        // s.t. it starts s or after
        // AND it starts at the end of the first cloth or before
        // AND exactly ends at t
        else {
            auto t_to_s_it = lower_bound(t_to_s[t].begin(), t_to_s[t].end(), s);
            if (t_to_s_it == t_to_s[t].end()) {
                cout << "No\n";
                continue;
            }
            if (*t_to_s_it <= *s_to_t_it + 1) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}