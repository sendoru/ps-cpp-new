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

    ll H, W, n;
    cin >> H >> W >> n;
    vector<array<ll, 2>> frags(n);

    ll max_h = 0, max_w = 0;

    for (int i = 0; i < n; i++) {
        cin >> frags[i][0] >> frags[i][1];
        max_h = max(max_h, frags[i][0]);
        max_w = max(max_w, frags[i][1]);
    }

    bool swapped = false;
    if (max_h != H) {
        swapped = true;
        for (int i = 0; i < n; i++) {
            swap(frags[i][0], frags[i][1]);
        }
        swap(H, W);
        swap(max_h, max_w);
    }

    multiset<array<ll, 3>> frag_set_by_h;
    multiset<array<ll, 3>> frag_set_by_w;

    for (int i = 0; i < n; i++) {
        frag_set_by_h.insert({frags[i][0], frags[i][1], i});
        frag_set_by_w.insert({frags[i][1], frags[i][0], i});
    }

    vector<array<ll, 2>> ans(n);
    ll cur_h = 0, cur_w = 0;
    bool is_h = true;
    while (!frag_set_by_h.empty()) {
        auto *cur_set = is_h ? &frag_set_by_h : &frag_set_by_w;
        ll cur_max = is_h ? max_h : max_w;
        while (!cur_set->empty() && cur_set->rbegin()->at(0) >= cur_max) {
            auto frag = *cur_set->rbegin();
            cur_set->erase(prev(cur_set->end()));
            ans[frag[2]] = {cur_h, cur_w};
            if (is_h) {
                // {cur_h, cur_w} = frag
                auto it = frag_set_by_w.find({frag[1], frag[0], frag[2]});
                frag_set_by_w.erase(it);
                cur_w += frag[1];
            } else {
                // {cur_w, cur_h} = fragq
                auto it = frag_set_by_h.find({frag[1], frag[0], frag[2]});
                frag_set_by_h.erase(it);
                cur_h += frag[1];
            }
        }
        if (!cur_set->empty()) {
            if (is_h) {
                max_h = (*cur_set->rbegin())[0];
            } else {
                max_w = (*cur_set->rbegin())[0];
            }
        }
        is_h = !is_h;
    }

    if (swapped) {
        for (auto &p : ans) {
            swap(p[0], p[1]);
        }
    }

    for (auto &p : ans) {
        cout << p[0] + 1 << ' ' << p[1] + 1 << '\n';
    }

    return 0;
}