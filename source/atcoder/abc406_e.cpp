// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> to_bin(ll n)
{
    vector<int> ans;
    while (n > 0) {
        ans.push_back(n % 2);
        n /= 2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

ll modpow(ll a, ll b, ll mod)
{
    ll ans = 1;
    while (b > 0) {
        if (b & 1) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

ll solve(ll n, int k)
{
    vector<int> bin = to_bin(n);
    int m = bin.size();
    vector<vector<vector<ll>>> cnt(m + 1, vector<vector<ll>>(k + 1, vector<ll>(2, 0)));
    auto sum = cnt;
    cnt[0][0][1] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= k; j++) {
            for (int l = 0; l < 2; l++) {
                // no bound
                if (l == 0) {
                    // add 0
                    cnt[i + 1][j][l] += cnt[i][j][l];
                    sum[i + 1][j][l] += sum[i][j][l];
                    sum[i + 1][j][l] %= MOD9;
                    // add 1
                    if (j != k) {
                        cnt[i + 1][j + 1][l] += cnt[i][j][l];
                        sum[i + 1][j + 1][l] += sum[i][j][l] + modpow(2, m - i - 1, MOD9) * cnt[i][j][l];
                        sum[i + 1][j + 1][l] %= MOD9;
                    }
                }
                // bound
                else {
                    if (bin[i] == 0) {
                        cnt[i + 1][j][l] += cnt[i][j][l];
                        sum[i + 1][j][l] += sum[i][j][l];
                        sum[i + 1][j][l] %= MOD9;
                    }
                    else {
                        cnt[i + 1][j][0] += cnt[i][j][l];
                        sum[i + 1][j][0] += sum[i][j][l];
                        sum[i + 1][j][0] %= MOD9;
                        if (j != k) {
                            cnt[i + 1][j + 1][l] += cnt[i][j][l];
                            sum[i + 1][j + 1][l] += sum[i][j][l] + modpow(2, m - i - 1, MOD9) * cnt[i][j][l];
                            sum[i + 1][j + 1][l] %= MOD9;
                        }
                    }
                }
            }
        }
    }

    return (sum[m][k][0] + sum[m][k][1]) % MOD9;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        int k;
        cin >> n >> k;
        cout << solve(n, k) << '\n';
    }

    return 0;
}