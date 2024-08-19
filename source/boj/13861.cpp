#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    double a;
    cin >> a;
    int n;
    cin >> n;
    if (n == 1) {
        assert(false);
    }
    double max_ratio = -1e12;
    double cur;
    cin >> cur;
    double min_val = cur;
    for (int i = 1; i < n; i++) {
        double next;
        cin >> next;
        if (next / min_val > max_ratio) {
            max_ratio = next / min_val;
        }
        if (next < min_val) {
            min_val = next;
        }
    }

    cout << fixed;
    cout.precision(2);
    cout << (max_ratio - 1) * a;

    return 0;
}