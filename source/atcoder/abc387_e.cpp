// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll get_digit_sum(string n) {
    ll sum = 0;
    for (char c : n) {
        sum += c - '0';
    }
    return sum;
}

ll solve_naive(string n) {
    ll n_ll = stoll(n);
    for (ll a = n_ll; a + 1 <= 2 * n_ll; a++) {
        string a_str = to_string(a);
        string app_str = to_string(a + 1);
        ll a_digit_sum = get_digit_sum(a_str);
        ll app_digit_sum = get_digit_sum(app_str);
        if (a % a_digit_sum == 0 && (a + 1) % app_digit_sum == 0) {
            return a;
        }
    }

    return -1;
}

string solve(string n) {
    string ret;
    if (n[0] == '1') {
        string smallest = "1";
        for (int i = 0; i < n.size() - 1; i++) {
            smallest += "0";
        }
        if (n == smallest) {
            ret = "1";
            for (int i = 0; i < n.size() - 3; i++) {
                ret += "0";
            }
            ret += "11";
        } else {
            ret = "2";
            for (int i = 0; i < n.size() - 1; i++) {
                ret += "0";
            }
        }
        return ret;
    } else if (n[0] <= '5') {
        ret += n[0] + 1;
        for (int i = 0; i < n.size() - 5; i++) {
            ret += "0";
        }
        ret += 8 - (ret[0] - '0') + '0';
        while (ret.size() < n.size()) {
            ret += "0";
        }
        return ret;
    } else {
        ret = "1";
        for (int i = 0; i < n.size() - 2; i++) {
            ret += "0";
        }
        ret += "11";
        return ret;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string n;
    cin >> n;

    if (n.length() <= 6) {
        cout << solve_naive(n) << '\n';
    } else {
        cout << solve(n) << '\n';
    }

    return 0;
}