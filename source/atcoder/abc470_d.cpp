// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> p(n), inv_p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        inv_p[p[i]] = i;
    }
    bool is_inv = false;
    while (q--) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            if (is_inv) {
                swap(inv_p[x], inv_p[y]);
                p[inv_p[x]] = x;
                p[inv_p[y]] = y;
            } else {
                swap(p[x], p[y]);
                inv_p[p[x]] = x;
                inv_p[p[y]] = y;
            }

        } else {
            is_inv = !is_inv;
        }
    }

    if (is_inv) {
        for (auto elem : inv_p) {
            cout << elem + 1 << ' ';
        }
    } else {
        for (auto elem : p) {
            cout << elem + 1 << ' ';
        }
    }

    return 0;
}