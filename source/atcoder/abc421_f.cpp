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

    list<int> ls = {0};
    int q;
    cin >> q;
    // vector of lst iterators
    vector<list<int>::iterator> iters(q);
    iters[0] = ls.begin();
    for (int i = 1; i <= q; i++) {
        int c;
        cin >> c;
        if (c == 1) {
            int x;
            cin >> x;
            iters[i] = ls.insert(iters[x], i);
        } else {
            int x, y;
            cin >> x >> y;
            auto itx = iters[x], ity = iters[y];
            // compair iterators
            if (itx == ity)
                continue;
            bool rev = true;
            auto it = itx, it_rev = itx;
            while (it != ls.end() || it_rev != ls.begin()) {
                if (it == ity) {
                    rev = false;
                    break;
                }
                if (it_rev == ity) {
                    rev = true;
                    break;
                }
                if (it != ls.end())
                    it++;
                if (it_rev != ls.begin())
                    it_rev--;
            }
            if (rev) {
                swap(itx, ity);
            }
            ll ans = 0;
            it = ++itx;
            while (it != ity) {
                ans += *it;
                it = ls.erase(it);
            }
            cout << ans << "\n";
        }
    }

    return 0;
}