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
        n++;

        vector<int> ans;
        for (int i = 0; i + 4 <= n; i += 4) {
            ans.push_back(i);
            ans.push_back(i + 1);
            ans.push_back(i + 3);
            ans.push_back(i + 2);
        }
        int rem = n % 4;
        for (int i = n - rem; i < n; i++) {
            ans.push_back(i);
        }
        for (int i = 1; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}