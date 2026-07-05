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

    int ans = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] > a[i + 1]) {
            ans++;
            a[i] = a[i + 1];
        }
    }

    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }

    return 0;
}