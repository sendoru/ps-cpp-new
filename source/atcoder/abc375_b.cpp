#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

double dist(pdd a, pdd b)
{
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pdd> dots(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> dots[i].first >> dots[i].second;
    }

    double ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += dist(dots[i], dots[(i + 1) % (n + 1)]);
    }

    cout << fixed << setprecision(10) << ans << '\n';

    return 0;
}