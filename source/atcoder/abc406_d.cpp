// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w, n;
    cin >> h >> w >> n;

    map<int, set<int>> by_x, by_y;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        by_x[x].insert(y);
        by_y[y].insert(x);
    }

    int q;
    cin >> q;
    while (q--) {
        int qt, coord;
        cin >> qt >> coord;
        if (qt == 1) {
            int x = coord;
            cout << by_x[x].size() << '\n';
            for (int y : by_x[x]) {
                by_y[y].erase(x);
            }
            by_x[x].clear();
        }
        else if (qt == 2) {
            int y = coord;
            cout << by_y[y].size() << '\n';
            for (int x : by_y[y]) {
                by_x[x].erase(y);
            }
            by_y[y].clear();
        }
    }

    return 0;
}