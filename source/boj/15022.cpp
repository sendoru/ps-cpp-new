#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

template <typename T, T (*op)(T, T), T (*e)()>
struct SegTree {
    int n;
    vector<T> tree;
    SegTree(int n) {
        this->n = 1;
        while (this->n < n) {
            this->n <<= 1;
        }
        tree.assign(this->n * 2, e());
    }
    SegTree(vector<T> &v) {
        int n = v.size();
        this->n = 1;
        while (this->n < n) {
            this->n <<= 1;
        }
        tree.assign(this->n * 2, e());
        copy(v.begin(), v.end(), tree.begin() + this->n);
        build();
    }
    void build() {
        for (int i = n - 1; i > 0; i--) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    void update(int i, T val) {
        i += n;
        tree[i] = val;
        for (i >>= 1; i > 0; i >>= 1) {
            tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    T query(int l, int r) {
        T resl = e(), resr = e();
        l += n;
        r += n;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                resl = op(resl, tree[l++]);
            }
            if (r & 1) {
                resr = op(tree[--r], resr);
            }
        }
        return op(resl, resr);
    }
};

int op(int a, int b) {
    return a + b;
}

int zero() {
    return 0;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pii> events;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        b *= -1;
        events.push_back({a, b});
    }
    vector<pii> team_score(n);
    map<pii, int> score_and_team_cnt;
    score_and_team_cnt[{0, 0}] = n;
    for (auto [a, b] : events) {
        pii prev = team_score[a];
        score_and_team_cnt[prev]--;
        pii curr = prev;
        curr.first++;
        curr.second += b;
        team_score[a] = curr;
        score_and_team_cnt[curr]++;
    }

    map<pii, int> score_to_index;
    int idx = 0;
    for (auto [score, cnt] : score_and_team_cnt) {
        score_to_index[score] = idx;
        idx += 1;
    }

    SegTree<int, op, zero> segtree(idx);
    for (int i = 0; i < n; i++) {
        team_score[i] = {0, 0};
    }

    segtree.update(score_to_index[{0, 0}], n);
    vector<int> ans;

    for (auto [a, b] : events) {
        pii prev = team_score[a];
        pii curr = prev;
        curr.first++;
        curr.second += b;
        team_score[a] = curr;
        segtree.update(score_to_index[prev], segtree.query(score_to_index[prev], score_to_index[prev] + 1) - 1);
        segtree.update(score_to_index[curr], segtree.query(score_to_index[curr], score_to_index[curr] + 1) + 1);
        int res = segtree.query(score_to_index[team_score[0]] + 1, idx);
        ans.push_back(res);
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] + 1 << '\n';
    }

    return 0;
}