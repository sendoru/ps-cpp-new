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
    vector<ll> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<bool> mask(1e6 + 1, false);
    for (int i = 0; i < n; i++) {
        mask[s[i]] = true;
    }

    sort(s.begin(), s.end());
    // find the count of triplets (a, b, c) such that b is average of a and c
    // a + c = 2 * b

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((s[i] + s[j]) % 2 != 0) {
                continue;
            }
            ans += mask[(s[i] + s[j]) / 2];
        }
    }

    cout << ans << endl;

    return 0;
}