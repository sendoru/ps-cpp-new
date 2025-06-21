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
    n--;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    for (int i = 0; i < n; i++) {
        vector<int> v(n - i);
        for (int j = 0; j < n - i; j++) {
            v[j] = d[i + j];
        }
        vector<int> s(n - i);
        s[0] = v[0];
        for (int j = 1; j < n - i; j++) {
            s[j] = s[j - 1] + v[j];
        }
        for (int j = 0; j < n - i; j++) {
            cout << s[j] << " ";
        }
        cout << "\n";
    }

    return 0;
}