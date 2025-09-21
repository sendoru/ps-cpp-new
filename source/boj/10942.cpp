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

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> is_pal(n, vector<int>(n, -1));

    function<int(int, int)> check = [&](int l, int r) -> int {
        if (l >= r)
            return 1;
        int &res = is_pal[l][r];
        if (res != -1)
            return res;
        if (a[l] != a[r])
            return res = 0;
        return res = check(l + 1, r - 1);
    };
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << check(l, r) << "\n";
    }

    return 0;
}