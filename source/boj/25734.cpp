#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct comp {
    bool operator()(const pii &a, const pii &b) const {
        return a.second != b.second ? a.second < b.second : a.first < b.first;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    set<pii> comp_s;
    set<pii, comp> comp_e;

    ll cur = 0;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int q, x;
        cin >> q >> x;
        if (q == 1 && comp_s.empty()) {
            comp_s.insert({x, x});
            comp_e.insert({x, x});
            cur = 1;
        } else if (q == 1) {
            // first segment whose s > x
            auto it_s = comp_s.lower_bound({x, -MOD1});

            // last segment whose e < x
            auto it_e = comp_e.upper_bound({-MOD1, x});

            bool merge_l = it_e != comp_e.begin() && prev(it_e)->second == x - 1;
            bool merge_r = it_s != comp_s.end() && it_s->first == x + 1;

            // case 1: add new segment with len 1
            if (!merge_l && !merge_r) {
                comp_s.insert({x, x});
                comp_e.insert({x, x});
                cur += 1;
            }

            // case 2: extend only left segment
            else if (merge_l && !merge_r) {
                pii seg = *prev(it_e);
                comp_s.erase(seg);
                comp_e.erase(seg);
                comp_s.insert({seg.first, x});
                comp_e.insert({seg.first, x});
                cur += x - seg.first + 1;
            }

            // case 3: extend only right segment
            else if (!merge_l && merge_r) {
                pii seg = *it_s;
                comp_s.erase(seg);
                comp_e.erase(seg);
                comp_s.insert({x, seg.second});
                comp_e.insert({x, seg.second});
                cur += seg.second - x + 1;
            }

            // case 4: merge left and right segment
            else {
                pii seg_l = *prev(it_e);
                pii seg_r = *it_s;
                comp_s.erase(seg_l);
                comp_e.erase(seg_r);
                comp_s.erase(seg_r);
                comp_e.erase(seg_l);
                comp_s.insert({seg_l.first, seg_r.second});
                comp_e.insert({seg_l.first, seg_r.second});

                ll left_len = x - seg_l.first;
                ll right_len = seg_r.second - x;
                ll total_len = left_len + right_len + 1;
                cur -= (left_len + 1) * left_len / 2;
                cur -= (right_len + 1) * right_len / 2;
                cur += (total_len + 1) * total_len / 2;
            }

        } else {
            // last segment whose s <= x
            auto it_s = comp_s.upper_bound({x, MOD1});
            it_s = prev(it_s);
            // case 1: remove segment with len 1
            if (it_s->first == it_s->second) {
                comp_s.erase(it_s);
                comp_e.erase(*it_s);
                cur -= 1;
            }

            // case 2: remove rightmost element of a segment
            else if (it_s->second == x) {
                pii seg = *it_s;
                comp_s.erase(seg);
                comp_e.erase(seg);
                comp_s.insert({seg.first, x - 1});
                comp_e.insert({seg.first, x - 1});
                cur -= x - seg.first + 1;
            }

            // case 3: remove leftmost element of a segment
            else if (it_s->first == x) {
                pii seg = *it_s;
                comp_s.erase(seg);
                comp_e.erase(seg);
                comp_s.insert({x + 1, seg.second});
                comp_e.insert({x + 1, seg.second});
                cur -= seg.second - x + 1;
            }

            // case 4: split into two segments
            else {
                pii seg = *it_s;
                comp_s.erase(seg);
                comp_e.erase(seg);
                comp_s.insert({seg.first, x - 1});
                comp_e.insert({seg.first, x - 1});
                comp_s.insert({x + 1, seg.second});
                comp_e.insert({x + 1, seg.second});
                ll left_len = x - seg.first;
                ll right_len = seg.second - x;
                ll total_len = left_len + right_len + 1;
                cur -= (total_len + 1) * total_len / 2;
                cur += (left_len + 1) * left_len / 2;
                cur += (right_len + 1) * right_len / 2;
            }
        }

        cout << cur << '\n';
    }

    return 0;
}