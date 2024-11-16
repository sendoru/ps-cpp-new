#pragma GCC optimize("O3")
#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int solve(vector<vector<int>> &dp, vector<int> &cards, int a, int b)
{
    if (dp[a][b] != -1) {
        return dp[a][b];
    }
    if (a == 0) {
        return dp[a][b] = 0;
    }
    int card_cnt = cards.size();
    int c = ((1 << card_cnt) - 1) ^ (a | b);
    for (int i = 0; i < card_cnt; i++) {
        if ((a & (1 << i)) == 0) {
            continue;
        }
        for (int j = 0; j < card_cnt; j++) {
            if ((c & (1 << j)) == 0) {
                continue;
            }
            if (cards[i] > cards[j]) {
                if (!solve(dp, cards, b, a ^ (1 << i) ^ (1 << j))) {
                    return dp[a][b] = 1;
                }
            }
        }
        if (!solve(dp, cards, b, a ^ (1 << i))) {
            return dp[a][b] = 1;
        }
    }
    return dp[a][b] = 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, l;
    cin >> n >> m >> l;

    vector<int> cards(n + m + l);
    for (int i = 0; i < n + m + l; i++) {
        cin >> cards[i];
    }

    vector<vector<int>> dp(1 << (n + m + l), vector<int>(1 << (n + m + l), -1));

    int a_init = (1 << n) - 1;
    int b_init = ((1 << m) - 1) << n;

    if (solve(dp, cards, a_init, b_init)) {
        cout << "Takahashi" << endl;
    }
    else {
        cout << "Aoki" << endl;
    }

    return 0;
}