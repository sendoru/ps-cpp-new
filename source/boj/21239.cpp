// see also https://www.acmicpc.net/problem/27654
// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

double solve(vector<vector<ll>> &v) {
    ll n = v.size();
    double ans = 0;
    double l = 0, r = 1e9, m;
    for (int _ = 0; _ < 70; _++) {
        m = (l + r) / 2;
        ll denom = 0, num = 0;
        for (int i = 0; i < n; i++) {
            // den1 * m - num1 < den2 * m - num2
            if (v[i][0] * m - v[i][1] < v[i][2] * m - v[i][3]) {
                num += v[i][1];
                denom += v[i][0];
            } else {
                num += v[i][3];
                denom += v[i][2];
            }
        }

        if ((double)num / denom >= m) {
            ans = max(ans, m);
            l = m;
        } else {
            r = m;
        }
    }

    return ans;
}

// O(n * 2^n) exhaustive search
double solve_naive(vector<vector<ll>> &v) {
    ll n = v.size();
    double ans = 0;
    for (int i = 0; i < (1 << n); i++) {
        ll denom = 0, num = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                num += v[j][1];
                denom += v[j][0];
            } else {
                num += v[j][3];
                denom += v[j][2];
            }
        }
        ans = max(ans, (double)num / denom);
    }

    return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < 200; i++) {
        vector<vector<ll>> v(10, vector<ll>(4));
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 4; k++) {
                v[j][k] = dist(g);
            }
        }

        double ans1 = solve(v);
        double ans2 = solve_naive(v);
        if (abs(ans1 - ans2) > 1e-6) {
            cout << "Mismatched! " << ans1 << ' ' << ans2 << '\n';
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 4; k++) {
                    cout << v[j][k] << ' ';
                }
                cout << '\n';
            }
            break;
        }
    }

    cout << "Done\n";
    return 0;
#else
    ll n;
    cin >> n;
    vector<vector<ll>> v(n, vector<ll>(4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> v[i][j];
        }
    }

    double ans = solve(v);
    cout << fixed << setprecision(12) << ans << '\n';
#endif

    return 0;
}