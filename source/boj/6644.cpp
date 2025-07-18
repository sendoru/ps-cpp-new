// #include "atcoder/all"
// #pragma GCC optimize("Ofast,unroll-loops")
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

    while (true) {
        vector<string> s, t;
        while (true) {
            string tmp;
            cin >> tmp;
            if (tmp == ".") {
                break;
            }
            s.push_back(tmp);
        }
        if (s.empty()) {
            break;
        }
        while (true) {
            string tmp;
            cin >> tmp;
            if (tmp == ".") {
                break;
            }
            t.push_back(tmp);
        }

        vector<string> st_unique;
        for (const auto &str : s) {
            st_unique.push_back(str);
        }
        for (const auto &str : t) {
            st_unique.push_back(str);
        }
        sort(st_unique.begin(), st_unique.end());
        st_unique.erase(unique(st_unique.begin(), st_unique.end()), st_unique.end());

        vector<int> s_idx(s.size()), t_idx(t.size());
        for (int i = 0; i < s.size(); i++) {
            s_idx[i] = lower_bound(st_unique.begin(), st_unique.end(), s[i]) - st_unique.begin();
        }
        for (int i = 0; i < t.size(); i++) {
            t_idx[i] = lower_bound(st_unique.begin(), st_unique.end(), t[i]) - st_unique.begin();
        }

        reverse(s_idx.begin(), s_idx.end());
        reverse(t_idx.begin(), t_idx.end());

        vector<vector<int>> min_len(s.size() + 1, vector<int>(t.size() + 1, 1e8));
        min_len[0][0] = 0;

        for (int i = 0; i <= s.size(); i++) {
            for (int j = 0; j <= t.size(); j++) {
                if (i > 0) {
                    min_len[i][j] = min(min_len[i][j], min_len[i - 1][j] + 1);
                }
                if (j > 0) {
                    min_len[i][j] = min(min_len[i][j], min_len[i][j - 1] + 1);
                }
                if (i > 0 && j > 0 && s_idx[i - 1] == t_idx[j - 1]) {
                    min_len[i][j] = min(min_len[i][j], min_len[i - 1][j - 1] + 1);
                }
            }
        }

        int cur_s = s.size(), cur_t = t.size();
        vector<int> ans_idx;
        while (cur_s > 0 || cur_t > 0) {
            if (cur_s == 0) {
                ans_idx.push_back(t_idx[cur_t - 1]);
                cur_t--;
            } else if (cur_t == 0) {
                ans_idx.push_back(s_idx[cur_s - 1]);
                cur_s--;
            } else {
                int pre_s = cur_s, pre_t = cur_t, pre_idx = 1e8;
                if (min_len[cur_s - 1][cur_t] + 1 == min_len[cur_s][cur_t] && pre_idx > s_idx[cur_s - 1]) {
                    pre_s = cur_s - 1;
                    pre_t = cur_t;
                    pre_idx = s_idx[cur_s - 1];
                }
                if (min_len[cur_s][cur_t - 1] + 1 == min_len[cur_s][cur_t] && pre_idx > t_idx[cur_t - 1]) {
                    pre_s = cur_s;
                    pre_t = cur_t - 1;
                    pre_idx = t_idx[cur_t - 1];
                }
                if (min_len[cur_s - 1][cur_t - 1] + 1 == min_len[cur_s][cur_t] && s_idx[cur_s - 1] == t_idx[cur_t - 1]) {
                    pre_s = cur_s - 1;
                    pre_t = cur_t - 1;
                    pre_idx = s_idx[cur_s - 1];
                }
                ans_idx.push_back(pre_idx);
                cur_s = pre_s;
                cur_t = pre_t;
            }
        }
        vector<string> ans;
        for (int idx : ans_idx) {
            ans.push_back(st_unique[idx]);
        }

        for (const auto &str : ans) {
            cout << str << ' ';
        }
        cout << ".\n";
    }

    return 0;
}