// #include "atcoder/all"
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
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        a[i].resize(l);
        for (int j = 0; j < l; j++) {
            cin >> a[i][j];
        }
    }

    int x, y;
    cin >> x >> y;
    x--;
    y--;
    cout << a[x][y];

    return 0;
}