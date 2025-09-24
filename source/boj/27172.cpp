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
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    vector<int> pos(*max_element(x.begin(), x.end()) + 1, -1);
    for (int i = 0; i < n; i++) {
        pos[x[i]] = i;
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        for (int j = x[i]; j < (int)pos.size(); j += x[i]) {
            if (pos[j] != -1) {
                ans[i]++;
                ans[pos[j]]--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}