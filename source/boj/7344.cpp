// #include "atcoder/all"
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

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        vector<pair<int, int>> v(k);
        for (int i = 0; i < k; i++) {
            cin >> v[i].first >> v[i].second;
        }

        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        k = v.size();
        for (int i = 0; i < k; i++) {
            v[i].second *= -1;
        }

        vector<int> ldsStack;
        for (int i = 0; i < k; i++) {
            auto iter = lower_bound(ldsStack.begin(), ldsStack.end(), v[i].second);
            if (iter == ldsStack.end())
                ldsStack.push_back(v[i].second);
            else
                *iter = v[i].second;
        }

        cout << ldsStack.size() << '\n';
    }

    return 0;
}