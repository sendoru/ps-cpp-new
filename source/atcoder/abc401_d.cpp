// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    string ans = s;
    for (int i = 0; i < n; i++) {
        if (ans[i] == '?') {
            if (i > 0 && ans[i - 1] == 'o') {
                ans[i] = '.';
            }
            else if (i < n - 1 && ans[i + 1] == 'o') {
                ans[i] = '.';
            }
        }
    }
    // segments of '?' in ans
    // start and length of segments
    vector<pii> segments;
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (ans[i] == '?') {
            if (start == -1) {
                start = i;
            }
        }
        else {
            if (start != -1) {
                segments.push_back({start, i - start});
                start = -1;
            }
        }
    }

    if (start != -1) {
        segments.push_back({start, n - start});
    }

    // addtional 'o's can be added
    int max_room = 0;
    for (auto seg : segments) {
        max_room += seg.second / 2 + seg.second % 2;
    }
    int o_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (ans[i] == 'o') {
            o_cnt++;
        }
    }
    int remain = k - o_cnt;
    if (remain == 0) {
        for (int i = 0; i < n; i++) {
            if (ans[i] == '?') {
                ans[i] = '.';
            }
        }
        cout << ans << '\n';
        return 0;
    }

    if (max_room > remain) {
        cout << ans << '\n';
        return 0;
    }

    else {
        for (auto seg : segments) {
            auto [start, len] = seg;
            if (len % 2) {
                for (int i = start; i < start + len; i += 2) {
                    ans[i] = 'o';
                }
                for (int i = start + 1; i < start + len; i += 2) {
                    ans[i] = '.';
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}