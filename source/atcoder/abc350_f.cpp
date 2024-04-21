#include "atcoder/all"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll plus_ll(ll a, ll b) { return a + b; }
ll zero() { return 0; }

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    atcoder::segtree<ll, plus_ll, zero> seg(100);
    seg.set(10, 3);
    seg.set(20, 5);
    seg.set(25, 7);
    cout << seg.prod(0, 21) << endl;
    cout << seg.prod(0, 26) << endl;
    cout << seg.prod(11, 26) << endl;
    cout << seg.prod(0, 100) << endl;
}