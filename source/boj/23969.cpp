#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    bool sorted = true;
    for (int i = n - 1; i >= 1; i--) {
        sorted = true;
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                sorted = false;
                k--;
                swap(v[j], v[j + 1]);
                if (k == 0) {
                    break;
                }
            }
        }
        if (k == 0 || sorted) {
            break;
        }
    }

    if (k == 0) {
        for (int i = 0; i < n; i++) {
            cout << v[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}