// #include "atcoder/all"
#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ld dist(pld a, pld b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pld> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        vector<int> route(k);
        for (int i = 0; i < k; i++) {
            cin >> route[i];
        }

        double total_dist = 0;
        for (int i = 0; i < k - 1; i++) {
            total_dist += dist(points[route[i]], points[route[i + 1]]);
        }

        cout << (ll)round(total_dist) << endl;
    }

    return 0;
}