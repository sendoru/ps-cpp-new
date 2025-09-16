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

int ccw(pii a, pii b, pii c) {
    ll area = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
    if (area > 0)
        return 1;
    if (area < 0)
        return -1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pii> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y;
        }
        vector<int> idxs(n);
        iota(idxs.begin(), idxs.end(), 0);

        // sort(p.begin(), p.end());
        // sort(p.begin() + 1, p.end(), [&](pii a, pii b) {
        //     int dir = ccw(p[0], a, b);
        //     if (dir != 0)
        //         return dir > 0;
        //     return a < b;
        // });
        sort(idxs.begin(), idxs.end(), [&](int i, int j) {
            return p[i] < p[j];
        });
        sort(idxs.begin() + 1, idxs.end(), [&](int i, int j) {
            int dir = ccw(p[idxs[0]], p[i], p[j]);
            if (dir != 0)
                return dir > 0;
            return p[i] > p[j];
        });

        auto iter = idxs.begin() + 2;
        while (iter != idxs.end() && ccw(p[idxs[0]], p[idxs[1]], p[*iter]) == 0) {
            iter++;
        }
        reverse(idxs.begin() + 1, iter);

        for (int i = 0; i < n; i++) {
            cout << idxs[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}