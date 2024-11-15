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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> h(n);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        int max_cont = 1;
        int cur_cont = 1;
        for (int i = 1; i < n; i++) {
            if (h[i] == h[i - 1]) {
                cur_cont++;
                max_cont = max(max_cont, cur_cont);
            } else {
                cur_cont = 1;
            }
        }

        cout << n - max_cont << '\n';
    }

    return 0;
}