// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<map<int, int>> dice(n);
    vector<int> k(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        for (int j = 0; j < k[i]; j++) {
            int a;
            cin >> a;
            dice[i][a]++;
        }
    }

    ld ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ld cnt = 0;
            for (auto [a, b] : dice[i]) {
                if (dice[j].count(a)) {
                    cnt += (ll)b * dice[j][a];
                }
            }
            ans = max(ans, cnt / ((ll)k[i] * k[j]));
        }
    }

    cout << fixed << setprecision(12) << ans << endl;

    return 0;
}