// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

double ans = MOD1;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pii> dots(3 * n);
    for (int i = 0; i < 3 * n; i++) {
        cin >> dots[i].first >> dots[i].second;
    }

    function<void()> solve = [&]() -> void {
        // n x 3
        vector<array<int, 3>> v;
        vector<bool> checked(3 * n);
        function<void()> pick_outer = [&]() -> void {
            if (v.size() == n) {
                vector<double> areas(n);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < 3; j++) {
                        areas[i] += dots[v[i][j]].first * dots[v[i][(j + 1) % 3]].second;
                        areas[i] -= dots[v[i][j]].second * dots[v[i][(j + 1) % 3]].first;
                    }
                    areas[i] = abs(areas[i]);
                    areas[i] /= 2.;
                }
                sort(areas.begin(), areas.end());
                ans = min(ans, areas[n - 1] - areas[0]);
                return;
            }
            array<int, 3> smallest = v.empty() ? array<int, 3>({-1, 0, 0}) : v.back();
            for (int i = smallest[0] + 1; i < 3 * n; i++) {
                for (int j = i + 1; j < 3 * n; j++) {
                    for (int k = j + 1; k < 3 * n; k++) {
                        if (!checked[i] && !checked[j] && !checked[k] && array<int, 3>({i, j, k}) > smallest) {
                            checked[i] = checked[j] = checked[k] = true;
                            v.push_back({i, j, k});
                            pick_outer();
                            v.pop_back();
                            checked[i] = checked[j] = checked[k] = false;
                        }
                    }
                }
            }
        };
        pick_outer();
    };

    solve();
    cout << fixed << setprecision(1) << ans << '\n';

    return 0;
}