#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int op_sum(int a, int b) {
    return a + b;
}
int e_sum() {
    return 0;
}

int global_idx;
bool f(int v) {
    return v <= global_idx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    vector<array<ll, 2>> cnt(m);
    for (int i = 0; i < m; i++) {
        cnt[i][0] = i;
        // cnt[i][1] is count
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        cnt[a[i]][1]++;
    }

    ll q;
    cin >> q;
    vector<array<ll, 3>> query(q);
    for (int i = 0; i < q; i++) {
        query[i][0] = i;
        cin >> query[i][1];
        query[i][1]--; // query[i][1] is x
        // query[i][2] is answer
    }
    sort(cnt.begin(), cnt.end(), [&](const array<ll, 2> &x, const array<ll, 2> &y) {
        if (x[1] == y[1]) {
            return x[0] < y[0];
        }
        return x[1] < y[1];
    });
    sort(query.begin(), query.end(), [&](const array<ll, 3> &x, const array<ll, 3> &y) {
        return x[1] < y[1];
    });

    atcoder::segtree<int, op_sum, e_sum> seg(m);

    int using_unique = 1;
    seg.set(cnt[0][0], 1);
    int nxt_idx = 1;
    for (; nxt_idx < m; nxt_idx++) {
        if (cnt[nxt_idx][1] == cnt[nxt_idx - 1][1]) {
            using_unique++;
            seg.set(cnt[nxt_idx][0], 1);
        } else {
            break;
        }
    }
    ll cur_added = n;
    for (int i = 0; i < q;) {
        ll x = query[i][1];
        if (x < a.size()) {
            query[i][2] = a[x] + 1;
            i++;
            continue;
        }
        ll interval;
        if (nxt_idx == m) {
            interval = 1e18;
        } else {
            interval = (cnt[nxt_idx][1] - cnt[nxt_idx - 1][1]) * using_unique;
        }
        if (x - cur_added < interval) {
            auto idx = (x - cur_added) % using_unique;
            global_idx = idx;
            // use segwalk to find idx-th unique number
            query[i][2] = seg.max_right<f>(0) + 1;
            i++;
        } else {
            cur_added += interval;
            using_unique++;
            seg.set(cnt[nxt_idx][0], 1);
            nxt_idx++;
            while (nxt_idx < m && cnt[nxt_idx][1] == cnt[nxt_idx - 1][1]) {
                using_unique++;
                seg.set(cnt[nxt_idx][0], 1);
                nxt_idx++;
            }
        }
    }

    sort(query.begin(), query.end(), [&](const array<ll, 3> &x, const array<ll, 3> &y) {
        return x[0] < y[0];
    });
    for (int i = 0; i < q; i++) {
        cout << query[i][2] << "\n";
    }

    return 0;
}