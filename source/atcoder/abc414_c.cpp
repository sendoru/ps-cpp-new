// #include "atcoder/all"
#pragma GCC optimize("O3,Ofast,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> to_nary(ll n, int base) {
    vector<int> digits;
    while (n > 0) {
        digits.push_back(n % base);
        n /= base;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, n;
    cin >> a >> n;
    ll n_len = to_string(n).length();

    ll ans = 0;
    for (ll i = 0; 2 * to_string(i).length() <= n_len + 1; i++) {
        // even len palindrome
        string left = to_string(i), right = to_string(i);
        reverse(right.begin(), right.end());
        if (i > 0) {
            ll pal = stoll(left + right);
            if (pal > n) {
                continue;
            }
            vector<int> pal_digits = to_nary(pal, a);
            vector<int> pal_digits_reversed = pal_digits;
            reverse(pal_digits_reversed.begin(), pal_digits_reversed.end());
            if (pal_digits == pal_digits_reversed) {
                ans += pal;
            }
        }

        // odd len palindrome
        for (int j = 0; j <= 9; j++) {
            ll pal = stoll(left + to_string(j) + right);
            if (i == 0) {
                pal = j;
            }
            if (pal > n) {
                continue;
            }
            vector<int> pal_digits = to_nary(pal, a);
            vector<int> pal_digits_reversed = pal_digits;
            reverse(pal_digits_reversed.begin(), pal_digits_reversed.end());
            if (pal_digits == pal_digits_reversed) {
                ans += pal;
            }
        }
    }

    cout << ans << endl;

    return 0;
}