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

    string a, b;
    cin >> a >> b;
    for (int i = 0; i < n; i++) {
        if (b[i] != '*' && a[i] != b[i]) {
            cout << "No";
            return 0;
        }
    }

    cout << "Yes";

    return 0;
}