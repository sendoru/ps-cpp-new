#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll base, ll exp, ll mod) {
    if (exp == 0) {
        return 1;
    }
    if (exp % 2 == 0) {
        ll half = modpow(base, exp / 2, mod);
        return half * half % mod;
    }
    return base * modpow(base, exp - 1, mod) % mod;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll modinv_2 = modpow(2, MOD9 - 2, MOD9);

    int t;
    cin >> t;
    while (t--) {
        ll a1, a2, a3;
        cin >> a1 >> a2 >> a3;
        // without loss of generality, let a1 <= a2
        if (a1 > a2) {
            swap(a1, a2);
        }

        if (a3 != max(a1, a2) && a3 != max(a1, a2) + 1) {
            cout << 0 << '\n';
            continue;
        }

        // edge case when a1 = 1
        if (a1 == 1) {
            if (a3 == a2 + 1) {
                cout << 45 << '\n';
            } else {
                ll whole = 9 * 9 * modpow(10, a2 - 1, MOD9);
                cout << (whole - 45) % MOD9 << '\n';
            }
            continue;
        }

        // count of (x1, x2, x3)
        // s.t x1 + x2 = x3
        // and x1 is a1 digit, x2 is a2 digit, x3 is a3 digit
        // and x1, x2, x3 are positive integers

        // 자릿수 올라가는 경우만 일단 생각하자
        // 안 올라가는 경우는 전체 경우에서 빼서 하면 되니까

        // 자릿수 같은 경우
        // ex: a1 = 3, a2 = 3
        // x1 = 100일때, 자릿수 넘어가는 x2 = (900 ~ 999)의 100가지
        // x1 = 101, 자릿수 넘어가는 x2 = (899 ~ 999)의 101가지
        // ...
        // x1 = 900, 자릿수 넘어가는 x2 = (100 ~ 999)의 900가지
        // x1 = (901 ~ 999)의 99가지 경우에 대해, 자릿수 넘어가는 x2 = (100 ~ 999)의 900가지
        // 경우의 수 = (100 + 101 + ... + 899) + 900 * 100
        // = 800 * 999 / 2 + 100 * 900

        if (a1 == a2) {
            atcoder::modint998244353 whole = 9 * 9 * atcoder::pow_mod(10, 2 * a1 - 2, MOD9);
            // ll whole = (((9 * 9 * modpow(10, a1 - 1, MOD9)) % MOD9) * modpow(10, a2 - 1, MOD9)) % MOD9;
            atcoder::modint998244353 over = 8 * atcoder::pow_mod(10, a1 - 1, MOD9);
            over *= (atcoder::pow_mod(10, a1, MOD9) + (MOD9 - 1));
            over *= modinv_2;
            over += 9 * atcoder::pow_mod(10, 2 * a1 - 2, MOD9);
            // ll over = (((9 * modpow(10, a1 - 1, MOD9) % MOD9 * (modpow(10, a1, MOD9) + (MOD9 - 1)) % MOD9 * modinv_2 % MOD9) + (9 * modpow(10, 2 * a1 - 2, MOD9) % MOD9)) + MOD9) % MOD9;
            if (a3 == a2) {
                cout << (whole - over).val() << '\n';
            } else {
                cout << over.val() << '\n';
            }
        }

        // a1 < a2
        // ex: a1 = 2, a2 = 4
        // x1 = 10일 때, 자릿수 넘어가는 x2 = (9990 ~ 9999)의 10가지
        // x1 = 11일 때, 자릿수 넘어가는 x2 = (9989 ~ 9999)의 11가지
        // ...
        // x1 = 99일 때, 자릿수 넘어가는 x2 = (9901 ~ 9999)의 99가지
        // 경우의 수 = 10 + 11 + ... + 99 = 90 * (10 + 99) / 2

        // a1 = 3이면 100 + 101 + ... 999 = 900 * (100 + 999) / 2
        else {
            atcoder::modint998244353 whole = 9 * 9 * atcoder::pow_mod(10, a1 - 1, MOD9);
            whole *= atcoder::pow_mod(10, a2 - 1, MOD9);
            atcoder::modint998244353 over = 9 * atcoder::pow_mod(10, a1 - 1, MOD9);
            over *= (11 * atcoder::pow_mod(10, a1 - 1, MOD9) + (MOD9 - 1));
            over *= modinv_2;
            if (a3 == a2) {
                cout << (whole - over).val() << '\n';
            } else {
                cout << over.val() << '\n';
            }
        }
    }

    return 0;
}