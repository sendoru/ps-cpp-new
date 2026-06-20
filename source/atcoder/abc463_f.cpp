// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> fact, inv_fact;
ll half;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1) {
            res = res * b % m;
        }
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

ll comb(ll n, ll k) {
    if (k > n || k < 0) {
        return 0;
    }
    return fact[n] * inv_fact[k] % MOD9 * inv_fact[n - k] % MOD9;
}

// P(B(n, p) = k) = C(n, k) * p^k * (1 - p)^(n - k)
ll binom_prob(ll n, ll p, ll k) {
    return comb(n, k) * modpow(p, k, MOD9) % MOD9 * modpow((1 - p + MOD9) % MOD9, n - k, MOD9) % MOD9;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fact.resize(1e6 + 10);
    inv_fact.resize(1e6 + 10);
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++) {
        fact[i] = fact[i - 1] * i % MOD9;
    }
    inv_fact.back() = modinv(fact.back(), MOD9);
    for (int i = (int)inv_fact.size() - 2; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD9;
    }

    half = modinv(2, MOD9);

    ll n;
    cin >> n;
    vector<array<ll, 2>> a(n);
    ll a_max = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a_max = max({a_max, a[i][0], a[i][1]});
    }
    bool case1 = false;
    for (int i = 0; i < n; i++) {
        if (a[i][0] == a_max && a[i][1] == a_max) {
            case1 = true;
            break;
        }
    }

    vector<array<ll, 2>> ans(n);

    if (case1) {
        ll cnt_base = 0, cnt_option = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][0] == a_max && a[i][1] == a_max) {
                cnt_base++;
            } else if (a[i][0] == a_max || a[i][1] == a_max) {
                cnt_option++;
            }
        }
        ll mm_expect = 0;
        for (ll i = 0; i <= cnt_option; i++) {
            mm_expect += half * binom_prob(cnt_option, half, i) % MOD9 * modinv(cnt_base + i, MOD9) % MOD9;
            mm_expect %= MOD9;
        }
        ll mx_expect = 0;
        for (ll i = 1; i <= cnt_option; i++) {
            mx_expect += half * binom_prob(cnt_option - 1, half, i - 1) % MOD9 * modinv(cnt_base + i, MOD9) % MOD9;
            mx_expect %= MOD9;
        }
        for (int i = 0; i < n; i++) {
            if (a[i][0] == a_max && a[i][1] == a_max) {
                ans[i][0] = ans[i][1] = mm_expect;
            } else if (a[i][0] == a_max) {
                ans[i][0] = mx_expect;
            } else if (a[i][1] == a_max) {
                ans[i][1] = mx_expect;
            } else {
                ans[i][0] = ans[i][1] = 0;
            }
        }
    }

    else {
        ll cnt_m = 0, cnt_m_minus_1_single = 0, cnt_m_minus_1_double = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][0] == a_max || a[i][1] == a_max) {
                cnt_m++;
            }
            if (a[i][0] == a_max - 1 && a[i][1] == a_max - 1) {
                cnt_m_minus_1_double++;
            } else if (a[i][0] == a_max - 1 || a[i][1] == a_max - 1) {
                cnt_m_minus_1_single++;
            }
        }

        // case 1: m + 1 winning players appear
        ll case1_prob = MOD9 + 1 - binom_prob(cnt_m, half, 0);
        case1_prob %= MOD9;

        ll cnt_option = cnt_m;
        ll cnt_base = 0;
        ll mx_expect = 0;
        for (ll i = 1; i <= cnt_option; i++) {
            mx_expect += half * binom_prob(cnt_option - 1, half, i - 1) % MOD9 * modinv(cnt_base + i, MOD9) % MOD9 % MOD9;
            mx_expect %= MOD9;
        }
        for (int i = 0; i < n; i++) {
            if (a[i][0] == a_max) {
                ans[i][0] = mx_expect;
            } else if (a[i][1] == a_max) {
                ans[i][1] = mx_expect;
            }
        }

        // case 2: all currently m winning players loses, max winning score becomes m
        ll case2_prob = binom_prob(cnt_m, half, 0);
        cnt_base = cnt_m_minus_1_double + cnt_m;
        cnt_option = 0;
        for (int i = 0; i < n; i++) {
            // one is m - 1 and the other is m
            if (a[i][0] + a[i][1] == 2 * a_max - 1) {
                cnt_base++;
            } else if (a[i][0] == a_max - 1 && a[i][1] <= a_max - 2) {
                cnt_option++;
            } else if (a[i][1] == a_max - 1 && a[i][0] <= a_max - 2) {
                cnt_option++;
            }
        }

        ll mm_expect = 0;
        for (ll i = 0; i <= cnt_option; i++) {
            mm_expect += binom_prob(cnt_option, half, i) % MOD9 * modinv(cnt_base + i, MOD9) % MOD9 * case2_prob % MOD9;
            mm_expect %= MOD9;
        }
        mx_expect = 0;
        for (ll i = 1; i <= cnt_option; i++) {
            mx_expect += half * binom_prob(cnt_option - 1, half, i - 1) % MOD9 * modinv(cnt_base + i, MOD9) % MOD9 * case2_prob % MOD9;
            mx_expect %= MOD9;
        }

        for (int i = 0; i < n; i++) {
            if (a[i][0] + a[i][1] == 2 * a_max - 1) {
                ans[i][0] = (ans[i][0] + mm_expect) % MOD9;
                ans[i][1] = (ans[i][1] + mm_expect) % MOD9;
            } else if (a[i][0] == a_max - 1 && a[i][1] <= a_max - 2) {
                ans[i][0] = (ans[i][0] + mx_expect) % MOD9;
            } else if (a[i][1] == a_max - 1 && a[i][0] <= a_max - 2) {
                ans[i][1] = (ans[i][1] + mx_expect) % MOD9;
            } else if (a[i][0] == a_max - 1 && a[i][1] == a_max - 1) {
                ans[i][0] = (ans[i][0] + half * mm_expect) % MOD9;
                ans[i][1] = (ans[i][1] + half * mm_expect) % MOD9;
            } else if (a[i][0] == a_max) {
                ans[i][0] = (ans[i][0] + mm_expect) % MOD9;
            } else if (a[i][1] == a_max) {
                ans[i][1] = (ans[i][1] + mm_expect) % MOD9;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i][0] << ' ' << ans[i][1] << "\n";
    }

    return 0;
}