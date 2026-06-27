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

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    int r_min = 123123, r_max = -1, c_min = 123123, c_max = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '#') {
                r_min = min(r_min, i);
                r_max = max(r_max, i);
                c_min = min(c_min, j);
                c_max = max(c_max, j);
            }
        }
    }

    for (int i = r_min; i <= r_max; i++) {
        for (int j = c_min; j <= c_max; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }

    return 0;
}