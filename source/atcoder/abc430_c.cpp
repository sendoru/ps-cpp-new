// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(int a, int b, const string &s) {
    int n = s.size();
    vector<int> a_cum(n + 1), b_cum(n + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') {
            a_cum[i + 1] = a_cum[i] + 1;
            b_cum[i + 1] = b_cum[i];
        } else {
            a_cum[i + 1] = a_cum[i];
            b_cum[i + 1] = b_cum[i] + 1;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int a_left = lower_bound(a_cum.begin(), a_cum.end(), a + a_cum[i - 1]) - a_cum.begin();
        int b_right = lower_bound(b_cum.begin(), b_cum.end(), b + b_cum[i - 1]) - b_cum.begin() - 1;
        ans += max(0, b_right - a_left + 1);
    }
    return ans;
}

ll solve_naive(int a, int b, const string &s) {
    int n = s.size();
    ll ans = 0;
    for (int l = 0; l < n; l++) {
        int a_count = 0, b_count = 0;
        for (int r = l; r < n; r++) {
            if (s[r] == 'a') {
                a_count++;
            } else {
                b_count++;
            }
            if (a <= a_count && b_count < b) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    string s;
    cin >> s;

    ll ans = solve(a, b, s);
    // ll ans_naive = solve_naive(a, b, s);
    // assert(ans == ans_naive);
    cout << ans << "\n";

    return 0;
}