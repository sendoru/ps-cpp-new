// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    int x_range = *max_element(x.begin(), x.end()) - *min_element(x.begin(), x.end());
    int y_range = *max_element(y.begin(), y.end()) - *min_element(y.begin(), y.end());

    cout << (x_range + 1) / 2 << " " << (y_range + 1) / 2 << endl;

    return 0;
}