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

    ll l, k, c;
    cin >> l >> k >> c;

    vector<ll> pos(k);

    for (int i = 0; i < k; i++) {
        cin >> pos[i];
        pos[i] = l - pos[i];
    }

    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());

    k = pos.size();

    ll ans = 1e12;
    vector<ll> cut_pos = {-(ll)1e12};

    vector<ll> seg_size(k + 1);
    seg_size[0] = pos[0];
    for (int i = 1; i < k; i++) {
        seg_size[i] = pos[i] - pos[i - 1];
    }
    seg_size[k] = l - pos[k - 1];

    // binary search
    ll lo = *max_element(seg_size.begin(), seg_size.end());
    ll hi = l + 1;

    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        ll cut_cnt = 0;
        ll cur_seg_size = 0;
        vector<ll> cur_cut_pos;

        for (int i = 0; i < k + 1; i++) {
            if (cur_seg_size + seg_size[i] <= mid) {
                cur_seg_size += seg_size[i];
            }
            else {
                cut_cnt++;
                cur_seg_size = seg_size[i];
                cur_cut_pos.push_back(pos[i - 1]);
            }
        }

        if (cut_cnt <= c) {
            hi = mid;
            if (mid < ans) {
                ans = mid;
                cut_pos = cur_cut_pos;
                if (cut_cnt < c) {
                    cut_pos.push_back(pos[k - 1]);
                }
            }
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans << ' ' << l - cut_pos.back() << '\n';

    return 0;
}