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

    int n, r;
    cin >> n >> r;
    deque<int> l(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }

    while (!l.empty() && l.front() == 1 && r > 0) {
        l.pop_front();
        r--;
    }
    while (!l.empty() && l.back() == 1 && r < l.size()) {
        l.pop_back();
    }

    int ans = l.size() + accumulate(l.begin(), l.end(), 0);
    cout << ans << '\n';

    return 0;
}