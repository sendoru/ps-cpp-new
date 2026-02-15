// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Circle {
    pll o;
    ll r;
};

struct Dsu {
    vector<int> parent, size;

    Dsu(int n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = find(parent[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

ll dist_square(pll a, pll b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double chain_length(Circle a, Circle b) {
    ll d_square = dist_square(a.o, b.o);
    if (d_square <= (a.r + b.r) * (a.r + b.r)) {
        return 0;
    }

    double r1 = min(a.r, b.r), r2 = max(a.r, b.r), d = sqrt(d_square);
    double theta2 = acos((r2 - r1) / d);
    double theta1 = M_PI - theta2;
    double l = sqrt(d_square - (r2 - r1) * (r2 - r1));
    return 2 * l + 2 * r2 * (M_PI - theta2) + 2 * r1 * (M_PI - theta1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<Circle> circles(n);
    for (int i = 0; i < n; i++) {
        cin >> circles[i].o.x >> circles[i].o.y >> circles[i].r;
    }

    Dsu dsu(n);
    vector<tuple<double, int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double l = chain_length(circles[i], circles[j]);
            edges.emplace_back(l, i, j);
        }
    }

    sort(edges.begin(), edges.end());

    double ans = 0;
    for (auto [l, i, j] : edges) {
        if (dsu.find(i) != dsu.find(j)) {
            dsu.unite(i, j);
            ans += l;
        }
    }

    cout << fixed << setprecision(12) << ans;

    return 0;
}