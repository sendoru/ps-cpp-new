#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<ll>> gen_perm(int n) {
    vector<vector<ll>> ret;
    vector<ll> perm(n);
    iota(perm.begin(), perm.end(), 0);
    do {
        ret.push_back(perm);
    } while (next_permutation(perm.begin(), perm.end()));
    return ret;
}

vector<ll> check_naive(int n) {
    vector<ll> ret(n + 1);
    for (int i = 1; i <= n; i++) {
        // count the number of permutations that has some i where perm[i] == i
        for (auto &perm : gen_perm(i)) {
            for (int j = 0; j < i; j++) {
                if (perm[j] == j) {
                    ret[i]++;
                    break;
                }
            }
        }
    }

    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> modinv = {0, 1, 500000004, 333333336, 250000002};

    vector<ll> dp(n + 1), fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD1;
    }
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        ll mp = i - 1;
        for (int j = i - 2; j >= 1; j--) {
            dp[i] += mp * dp[j];
            dp[i] %= MOD1;
            mp *= j;
            mp %= MOD1;
        }
        dp[i] += mp;
        dp[i] %= MOD1;
    }

    // auto naive = check_naive(n);

    ll ans = fact[n / 4 * 4] - dp[n / 4 * 4];
    ans += MOD1;
    ans %= MOD1;
    for (ll i = 1; i <= n % 4; i++) {
        ans *= (n - i + 1);
        ans %= MOD1;
        ans *= modinv[i];
        ans %= MOD1;
    }

    cout << ans << '\n';

    return 0;
}