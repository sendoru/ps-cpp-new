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
    vector<int> a(n);
    vector<int> cnt_by_height(q * 3 + 10);
    int offset = 0;
    while (q--) {
        int t, x;
        cin >> t >> x;
        if (t == 1) {
            x--;
            a[x]++;
            cnt_by_height[a[x]]++;
            if (cnt_by_height[a[x]] == n) {
                offset = a[x];
            }
        } else {
            int cnt = 0;
            if (x + offset < cnt_by_height.size()) {
                cnt = cnt_by_height[x + offset];
            }
            cout << cnt << "\n";
        }
    }

    return 0;
}