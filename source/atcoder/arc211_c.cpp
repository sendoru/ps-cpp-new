// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Segment {
    char ch;
    int left, right;
    ll max_r;
    ll max_r_cnt;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    vector<Segment> segments;
    char prev_char = s[0];

    segments.push_back({s[0], 0, 0, r[0], 1});
    for (int i = 1; i < n; i++) {
        if (s[i] == prev_char) {
            segments.back().right = i;
            if (r[i] > segments.back().max_r) {
                segments.back().max_r = r[i];
                segments.back().max_r_cnt = 1;
            } else if (r[i] == segments.back().max_r) {
                segments.back().max_r_cnt++;
            }
        } else {
            segments.push_back({s[i], i, i, r[i], 1});
            prev_char = s[i];
        }
    }

    if (segments[0].ch == '#') {
        segments.erase(segments.begin());
    }
    if (segments.back().ch == '#') {
        segments.pop_back();
    }

    ll ans = 0;
    ll global_max = 0;
    for (auto& seg : segments) {
        global_max = max(global_max, seg.max_r);
    }

    for (int i = 1; i < segments.size(); i += 2) {
        ll cur_max_r = max({segments[i - 1].max_r, segments[i].max_r, segments[i + 1].max_r});
        if (cur_max_r == global_max) {
            ans += segments[i - 1].max_r_cnt * segments[i + 1].max_r_cnt;
        }
    }

    cout << ans << "\n";

    return 0;
}

/*
11
#..#.##.#..
192 1223 192 211 182 192 182 192 182 211 182
*/