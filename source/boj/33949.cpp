// #include "atcoder/all"
#pragma GCC optimize("O3,Ofast,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll INF = (ll)1e18;

// from atcoder library
template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S> &v) : _n(int(v.size())) {
        log = ceil(log2(_n));
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)>
    int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n)
            return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0)
                l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)>
    int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0)
            return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

array<ll, 4> maxSumId() {

    // 전체구간 합 = 0
    // 조건없음 합 = -INF
    return {-INF, -INF, -INF, -INF};
}

// 각 구간에 대해, 4개의 조건 하에서 연속합의 최댓값을 구해야 할 것 같다.
// 1. 왼쪽 끝을 포함하는 경우
// 2. 오른쪽 끝을 포함하는 경우
// 3. 왼쪽 끝과 오른쪽 끝 전부 포함 (=구간 전체)
// 4. 둘 다 신경 안써도 되는 경우
// kSum[n + 1][4]
// [i][0]: 왼쪽끝
// [i][1]: 오른쪽끝
// [i][2]: 전체구간
// [i][3]: 조건 상관없음

array<ll, 4> maxSumOP(array<ll, 4> l, array<ll, 4> r) {
    array<ll, 4> ret;
    // 0: 왼쪽 끝
    // (l의 왼쪽 끝) or (l의 전체 + r의 왼쪽 끝)
    ret[0] = max(l[0], l[2] + r[0]);
    // 1: 오른쪽 끝
    // (r의 오른쪽 끝) or (r의 전체 + l의 오른쪽 끝)
    ret[1] = max(r[1], r[2] + l[1]);
    // 2: 전체 구간
    // (l의 전체구간 + r의 전체구간)
    ret[2] = l[2] + r[2];
    // 3: 조건 없음
    // (l의 조건없음) or (r의 조건없음) or (l의 오른쪽끝 + r의 왼쪽끝)
    ret[3] = max(max(l[3], r[3]), l[1] + r[0]);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int s, q;
    cin >> s >> q;
    vector<ll> a(s);
    vector<array<ll, 4>> st_base(s, array<ll, 4>()), st_base2(s, array<ll, 4>());
    for (int i = 0; i < s; i++) {
        a[i] = 0;
        st_base[i][0] = a[i]; // 왼쪽 끝
        st_base[i][1] = a[i]; // 오른쪽 끝
        st_base[i][2] = a[i]; // 전체 구간
        st_base[i][3] = a[i]; // 조건 상관 없음

        st_base2[i][0] = max(0ll, -a[i]);
        st_base2[i][1] = max(0ll, -a[i]);
        st_base2[i][2] = -a[i];
        st_base2[i][3] = max(0ll, -a[i]);
    }

    segtree<array<ll, 4>, maxSumOP, maxSumId> st(st_base);
    segtree<array<ll, 4>, maxSumOP, maxSumId> st2(st_base2);

    ll all_sum = 0;

    while (q--) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int idx, diff;
            cin >> idx >> diff;
            idx--;
            ll val = a[idx] + diff;
            a[idx] = val;
            all_sum += diff;

            st.set(idx, {val, val, val, val});
            st2.set(idx, {max(0ll, -val), max(0ll, -val), -val, max(0ll, -val)});
        } else {
            // 최대 구간 합이 0, s - 1 경계를 미포함
            ll ans = st.prod(0, s)[3];

            // 최대 구간 합이 0, s - 1 경계를 포함
            ll rev_min = st2.prod(0, s - 1)[3];
            rev_min = max(rev_min, st2.prod(1, s)[3]);
            rev_min *= -1;

            ans = max(ans, all_sum - rev_min);
            cout << ans << '\n';
        }
    }

    return 0;
}