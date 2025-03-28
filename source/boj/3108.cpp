// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    vector<int> parent, sz;
    Dsu(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (sz[x] < sz[y]) {
                swap(x, y);
            }
            parent[y] = x;
            sz[x] += sz[y];
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return sz[find(x)];
    }
};

struct Rect {
    int x1, y1, x2, y2;
    Rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool inside(int x, int y) const {
        return x1 <= x && x <= x2 && y1 <= y && y <= y2;
    }
    bool inside(pii dot) const {
        return inside(dot.first, dot.second);
    }
    bool on_edge(int x, int y) const {
        return (x == x1 || x == x2) && (y >= y1 && y <= y2) ||
               (y == y1 || y == y2) && (x >= x1 && x <= x2);
    }
    bool on_edge(pii dot) const {
        return on_edge(dot.first, dot.second);
    }
    bool intersect(const Rect &rhs) const {
        vector<pii> lhs_dots = {
            {x1, y1}, {x1, y2}, {x2, y2}, {x2, y1}};
        for (pii dot : lhs_dots) {
            if (rhs.on_edge(dot)) {
                return true;
            }
        }
        vector<pii> rhs_dots = {
            {rhs.x1, rhs.y1}, {rhs.x1, rhs.y2}, {rhs.x2, rhs.y2}, {rhs.x2, rhs.y1}};
        for (pii dot : rhs_dots) {
            if (this->on_edge(dot)) {
                return true;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (rhs_dots[i].first == rhs_dots[(i + 1) % 4].first) {
                int x = rhs_dots[i].first;
                if (x < x1 || x > x2) {
                    continue;
                }
                if (rhs.y1 <= y1 && y1 <= rhs.y2) {
                    return true;
                }
                if (rhs.y1 <= y2 && y2 <= rhs.y2) {
                    return true;
                }
            } else {
                int y = rhs_dots[i].second;
                if (y < y1 || y > y2) {
                    continue;
                }
                if (rhs.x1 <= x1 && x1 <= rhs.x2) {
                    return true;
                }
                if (rhs.x1 <= x2 && x2 <= rhs.x2) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<Rect> rects;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rects.emplace_back(x1, y1, x2, y2);
    }

    Dsu dsu(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rects[i].intersect(rects[j])) {
                dsu.unite(i, j);
            }
        }
    }

    vector<int> cc;
    for (int i = 0; i < n; i++) {
        cc.push_back(dsu.find(i));
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());

    int ans = cc.size();
    for (int i = 0; i < n; i++) {
        if (rects[i].on_edge(0, 0)) {
            ans--;
            break;
        }
    }

    cout << ans << '\n';

    return 0;
}