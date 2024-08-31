#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll INF = 2e18;

// from atcoder library
template <class S, S (*op)(S, S), S (*e)()>
struct segtree {
public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S> &v) : _n(int(v.size()))
    {
        log = ceil(log2(_n));
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x)
    {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) const
    {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const
    {
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
    int max_right(int l) const
    {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>
    int max_right(int l, F f) const
    {
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
    int min_left(int r) const
    {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>
    int min_left(int r, F f) const
    {
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

array<ll, 4> maxSumId()
{

    return {0, 0, 0, 0};
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

array<ll, 4> maxSumOP(array<ll, 4> l, array<ll, 4> r)
{
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

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<vector<ll>> points(n, vector<ll>(3));
    vector<ll> x_coords, y_coords;
    for (int i = 0; i < n; i++) {
        cin >> points[i][1] >> points[i][0] >> points[i][2];
        x_coords.push_back(points[i][0]);
        y_coords.push_back(points[i][1]);
    }

    // coord comp
    sort(x_coords.begin(), x_coords.end());
    x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());

    for (int i = 0; i < n; i++) {
        points[i][0] = lower_bound(x_coords.begin(), x_coords.end(), points[i][0]) - x_coords.begin();
        points[i][1] = lower_bound(y_coords.begin(), y_coords.end(), points[i][1]) - y_coords.begin();
    }

    sort(points.begin(), points.end());

    ll ans = 0;
    int idx = 0;

    for (int i = 0; i < x_coords.size(); i++) {

        while (idx < n && points[idx][0] < i) {
            idx++;
        }

        vector<array<ll, 4>> wSum(y_coords.size(), {0, 0, 0, 0});
        segtree<array<ll, 4>, maxSumOP, maxSumId> seg(wSum);
        for (int j = idx; j < n; j++) {
            array<ll, 4> cur;
            for (int i = 0; i < 4; i++) {
                cur[i] = points[j][2] + seg.get(points[j][1])[3];
            }
            // update
            seg.set(points[j][1], cur);
            if (j == n - 1 || points[j][0] != points[j + 1][0]) {
                ans = max(ans, seg.all_prod()[3]);
            }
        }
    }

    cout << ans;

    return 0;
}