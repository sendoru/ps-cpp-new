// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(ll r) {
    if (r < 10) {
        return 0;
    }
    if (r < 20) {
        return 1;
    }
    ll ans = 0;
    string r_string = to_string(r);
    for (ll digit = 2; digit < r_string.size(); digit++) {
        for (ll top_digit = 1; top_digit <= 9; top_digit++) {
            ans += pow(top_digit, digit - 1);
        }
    }

    for (ll top_digit = 1; top_digit < r_string[0] - '0'; top_digit++) {
        ans += pow(top_digit, r_string.size() - 1);
    }

    string sub_r = r_string.substr(1);
    if (sub_r != "") {
        for (ll i = sub_r.length() - 1; i >= 0; i--) {
            if (sub_r[i] >= r_string[0]) {
                for (ll j = i; j < sub_r.length(); j++) {
                    sub_r[j] = r_string[0] - 1;
                }
            }
        }

        for (ll i = 0, j = (ll)sub_r.size() - 1; j >= 0; i++, j--) {
            ans += (ll)(sub_r[j] - '0') * pow((ll)r_string[0] - '0', i);
        }
        ans++;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll l, r;
    cin >> l >> r;
    ll r_ans = solve(r);
    ll l_ans = solve(l - 1);
    cout << r_ans - l_ans << '\n';

    return 0;
}