// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll MOD = 180;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    if (n % 2) {
        cout << "NO";
        return 0;
    }

    int v_sum = accumulate(v.begin(), v.end(), 0);
    v_sum %= MOD;
    if (v_sum % 2) {
        cout << "NO";
        return 0;
    }

    vector<vector<int>> dp(n + 1, vector<int>(MOD, -1));
    for (int i = 0; i < n; i++) {
        auto dp_new = dp;
        if (dp_new[1][v[i] % MOD] == -1) {
            dp_new[1][v[i] % MOD] = i;
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < MOD; k++) {
                if ((j == 0 && k == 0) || dp[j][k] != -1) {
                    int nk = (k + v[i]) % MOD;
                    if (dp_new[j + 1][nk] == -1) {
                        dp_new[j + 1][nk] = i;
                    }
                }
            }
        }
        dp = dp_new;
    }
    int cur_n = n / 2, cur_theta = v_sum / 2;
    if (dp[cur_n][cur_theta] == -1) {
        cur_theta = (cur_theta + MOD / 2) % MOD;
    }
    if (dp[cur_n][cur_theta] == -1) {
        cout << "NO";
        return 0;
    }

    vector<bool> check(n, false);
    while (cur_n) {
        int idx = dp[cur_n][cur_theta];
        check[idx] = true;
        cur_theta = (cur_theta - v[idx] + MOD) % MOD;
        cur_n--;
    }

    vector<int> odd, even;
    for (int i = 0; i < n; i++) {
        if (check[i]) {
            odd.push_back(i);
        } else {
            even.push_back(i);
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n / 2; i++) {
        cout << odd[i] + 1 << ' ' << even[i] + 1 << ' ';
    }

    return 0;
}