// #include "atcoder/all"
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

    ll n, t;
    cin >> n >> t;

    string s;
    cin >> s;

    vector<int> v;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'R') {
            v.push_back(1);
        } else if (s[i] == 'S') {
            v.push_back(2);
        } else {
            v.push_back(4);
        }
    }

    vector<int> segments;
    vector<int> type_pairs;
    segments.push_back(0);
    int cur = 0;
    for (int i = 0; i < n; i++) {
        cur |= v[i];
        if (cur == 7) {
            cur ^= v[i];
            segments.push_back(i);
            type_pairs.push_back(cur);
            cur = v[i];
        }
    }

    segments.push_back(n);
    type_pairs.push_back(cur);

    vector<int> ans(n);
    for (int i = 0; i < segments.size() - 1; i++) {
        int s = segments[i], e = segments[i + 1];
        int type = type_pairs[i];

        int win, lose;
        if (type == 3) {
            win = 1, lose = 2;
        } else if (type == 5) {
            win = 4, lose = 1;
        } else if (type == 6) {
            win = 2, lose = 4;
        } else { // all elements are same
            for (int j = s; j < e; j++) {
                ans[j] = v[j];
            }
            continue;
        }

        vector<int> win_idx, lose_idx;
        for (int j = s; j < e; j++) {
            if (v[j] == win) {
                win_idx.push_back(j);
            } else if (v[j] == lose) {
                lose_idx.push_back(j);
            }
        }

        // each lose idx is --ed by 1 for each iteration if possible (lose_idx[j] -> lose_idx[j] - t)
        // but it should be at least s + j
        for (int j = 0; j < lose_idx.size(); j++) {
            lose_idx[j] = max((ll)s + j, lose_idx[j] - t);
        }
        for (int j = 0; j < lose_idx.size(); j++) {
            ans[lose_idx[j]] = lose;
        }
        for (int j = s; j < e; j++) {
            if (ans[j] == 0) {
                ans[j] = win;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] == 1) {
            cout << 'R';
        } else if (ans[i] == 2) {
            cout << 'S';
        } else {
            cout << 'P';
        }
    }

    return 0;
}