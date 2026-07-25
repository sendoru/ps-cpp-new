#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int max_int(int a, int b) {
    return max(a, b);
}

int e() {
    return -1e9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    atcoder::segtree<int, max_int, e> seg(p.size() + 1);
    seg.set(0, 0);
    int offset = 0;
    int cur_max = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] < cur_max) {
            int cand = seg.prod(0, p[i]) + 1;
            seg.set(p[i], cand);
        } else {
            offset++;
            seg.set(p[i], seg.all_prod());
            cur_max = p[i];
        }
    }

    cout << seg.all_prod() + offset;

    return 0;
}