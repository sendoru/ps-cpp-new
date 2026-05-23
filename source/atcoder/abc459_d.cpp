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

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        vector<int> cnt(26);
        int max_cnt = 0;
        for (char c : s) {
            cnt[c - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            max_cnt = max(max_cnt, cnt[i]);
        }
        if (max_cnt <= (s.size() + 1) / 2) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
            continue;
        }

        map<char, int> char_to_cnt_map;
        for (char c : s) {
            char_to_cnt_map[c]++;
        }
        vector<pair<char, int>> char_to_cnt(char_to_cnt_map.begin(), char_to_cnt_map.end());
        sort(char_to_cnt.begin(), char_to_cnt.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
            return a.second > b.second;
        });

        string ans(s.size(), ' ');
        int idx = 0;
        for (int i = 0; i < char_to_cnt.size(); i++) {
            char c = char_to_cnt[i].first;
            int cnt = char_to_cnt[i].second;
            for (int j = 0; j < cnt; j++) {
                ans[idx] = c;
                idx += 2;
                if (idx >= s.size()) {
                    idx = 1;
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}