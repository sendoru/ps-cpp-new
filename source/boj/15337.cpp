// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct SegTree {
    vector<int> tree;
    int size;

    SegTree(int n) {
        size = 1;
        while (size < n)
            size <<= 1;
        tree.assign(size * 2, 0);
    }

    void update(int idx, int val) {
        idx += size;
        tree[idx] = val;
        while (idx > 1) {
            idx >>= 1;
            tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
        }
    }

    int query(int l, int r) {
        l += size;
        r += size;
        int res = 0;
        while (l < r) {
            if (l & 1)
                res = res + tree[l++];
            if (r & 1)
                res = res + tree[--r];
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    int query(int idx) {
        return tree[idx + size];
    }
};

int solve_1(const vector<pii> &se) {
    auto se_sorted = se;
    sort(se_sorted.begin(), se_sorted.end(), [](const pii &a, const pii &b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first > b.first;
    });

    vector<int> range_s_sum(se.size()), range_e_sum(se.size());
    vector<int> s_imos((int)1e5 + 1), e_imos((int)1e5 + 1);
    for (auto &[s, e] : se) {
        s_imos[s]++;
        e_imos[e]++;
    }
    for (int i = 1; i < (int)s_imos.size(); i++) {
        s_imos[i] += s_imos[i - 1];
        e_imos[i] += e_imos[i - 1];
    }

    for (int i = 0; i < (int)se_sorted.size(); i++) {
        range_s_sum[i] = s_imos[se_sorted[i].second - 1] - s_imos[se_sorted[i].first - 1] - 1;
        range_e_sum[i] = e_imos[se_sorted[i].second] - e_imos[se_sorted[i].first] - 1;
    }

    SegTree seg((int)1e5 + 1);
    vector<int> range_include_cnt(se_sorted.size());

    int idx = 0;
    for (int i = 0; i < (int)se_sorted.size(); i++) {
        if (i == (int)se_sorted.size() - 1 || se_sorted[i] != se_sorted[i + 1]) {
            while (idx <= i) {
                range_include_cnt[idx] = seg.query(se_sorted[i].first, se_sorted[i].second + 1);
                idx++;
            }
        }
        int seg_idx = se_sorted[i].second;
        seg.update(seg_idx, seg.query(seg_idx) + 1);
    }

    int ans = 0;
    for (int i = 0; i < (int)se_sorted.size(); i++) {
        int cur = range_s_sum[i] + range_e_sum[i] - range_include_cnt[i] + 1;
        ans = max(ans, cur);
    }

    return ans;
}

int solve_2(const vector<pii> &se) {
    vector<pii> imos;
    for (const auto &p : se) {
        imos.emplace_back(p.first, 1);
        imos.emplace_back(p.second, -1);
    }
    sort(imos.begin(), imos.end());

    int ans = 0, cur = 0;
    for (const auto &p : imos) {
        cur += p.second;
        ans = max(ans, cur);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pii> se(n);
    for (int i = 0; i < n; i++) {
        cin >> se[i].first >> se[i].second;
    }

    cout << solve_1(se) << ' ' << solve_2(se) << '\n';

    return 0;
}