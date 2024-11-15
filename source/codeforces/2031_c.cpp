// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<int>> a = {
    {1, 10, 26},
    {2, 3},
    {4, 5},
    {6, 7},
    {8, 9},
    {11, 12},
    {13, 14},
    {15, 16},
    {17, 18},
    {19, 20},
    {21, 22},
    {23, 27},
    {24, 25}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> paint_27(27);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            paint_27[a[i][j] - 1] = i + 4e5;
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n % 2 == 1 && n <= 26) {
            cout << "-1\n";
        } else if (n % 2 == 0) {
            for (int i = 1; i <= n / 2; i++) {
                cout << i * 2 << " " << i * 2 << " ";
            }
            cout << '\n';
        } else {
            for (int i = 1; i <= (n - 27) / 2; i++) {
                cout << i * 2 << " " << i * 2 << " ";
            }
            for (int i = 0; i < 27; i++) {
                cout << paint_27[i] << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}