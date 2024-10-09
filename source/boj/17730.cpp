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
    int n;
    vector<ll> tree;
    SegTree(int n) : n(n), tree(4 * n) {}

    void update(int idx, ll val) {
        update(1, 0, n - 1, idx, val);
    }

    void update(int node, int start, int end, int idx, ll val) {
        if (idx < start || end < idx) {
            return;
        }
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, idx, val);
        update(node * 2 + 1, mid + 1, end, idx, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }

    ll query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return 0;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
    }
};

// i = 0, 1, ... v.size() - 1에 대해,
// v의 부분배열 v[0..=i]의 inversion 개수를 반환
// i는 이미 좌표 압축된 상태여야 함
vector<ll>
count_inversion(vector<int> &v) {
    int n = v.size();
    vector<ll> ret(n);
    ll cur = 0;
    SegTree st(*max_element(v.begin(), v.end()) + 10);
    for (int i = 0; i < n; i++) {
        cur += st.query(v[i] + 1, st.n - 1);
        ret[i] = cur;
        st.update(v[i], st.query(v[i], v[i]) + 1);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    auto v_unique = v;
    sort(v_unique.begin(), v_unique.end());
    v_unique.erase(unique(v_unique.begin(), v_unique.end()), v_unique.end());

    for (int i = 0; i < n; i++) {
        v[i] = lower_bound(v_unique.begin(), v_unique.end(), v[i]) - v_unique.begin();
    }

    SegTree st(n + 10);
    for (int i = 0; i < n; i++) {
        st.update(i, 1);
    }

    vector<vector<int>> coord_by_val(n);
    for (int i = 0; i < n; i++) {
        coord_by_val[v[i]].push_back(i);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        auto &cur = coord_by_val[i];
        int l = 0, r = cur.size() - 1;
        while (l <= r) {
            int l_cost = st.query(0, cur[l] - 1);
            int r_cost = st.query(cur[r] + 1, n);
            if (l_cost < r_cost) {
                ans += l_cost;
                st.update(cur[l], st.query(cur[l], cur[l]) - 1);
                l++;
            } else {
                ans += r_cost;
                st.update(cur[r], st.query(cur[r], cur[r]) - 1);
                r--;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}