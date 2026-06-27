// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct MaxSegTree2D {
    int _h, _w;
    vector<vector<ll>> data;

    MaxSegTree2D(int h, int w)
    {
        _h = 1;
        while (_h < h) {
            _h <<= 1;
        }
        _w = 1;
        while (_w < w) {
            _w <<= 1;
        }
        data.assign(2 * _h, vector<ll>(2 * _w, 0));
    }

    void update(int r, int c, ll x)
    {
        r += _h;
        c += _w;
        data[r][c] = x;
        for (int i = c; i > 1; i >>= 1) {
            data[r][i >> 1] = max(data[r][i], data[r][i ^ 1]);
        }
        for (int i = r; i > 1; i >>= 1) {
            int j = c;
            while (j > 0) {
                data[i >> 1][j] = max(data[i][j], data[i ^ 1][j]);
                j >>= 1;
            }
        }
    }

    ll query_inner(int r, int c1, int c2)
    {
        ll res = 0;
        c1 += _w;
        c2 += _w;
        while (c1 < c2) {
            if (c1 & 1) {
                res = max(res, data[r][c1]);
                c1++;
            }
            if (c2 & 1) {
                c2--;
                res = max(res, data[r][c2]);
            }
            c1 >>= 1;
            c2 >>= 1;
        }
        return res;
    }

    ll query(int r1, int c1, int r2, int c2)
    {
        ll res = 0;
        r1 += _h;
        r2 += _h;
        while (r1 < r2) {
            if (r1 & 1) {
                res = max(res, query_inner(r1, c1, c2));
                r1++;
            }
            if (r2 & 1) {
                r2--;
                res = max(res, query_inner(r2, c1, c2));
            }
            r1 >>= 1;
            r2 >>= 1;
        }
        return res;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w, q;
    cin >> h >> w >> q;
    MaxSegTree2D seg(h, w);
    vector<tuple<int, int, char>> queries(q + 1);
    queries[0] = {h, w, 'A'};
    for (int i = 1; i <= q; i++) {
        int r, c;
        char ch;
        cin >> r >> c >> ch;
        queries[i] = {r, c, ch};
        seg.update(r - 1, c - 1, i);
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int idx = seg.query(i, j, h, w);
            cout << get<2>(queries[idx]);
        }
        cout << '\n';
    }

    return 0;
}