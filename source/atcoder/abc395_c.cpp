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

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> val_to_idx((int)1e6 + 1);
    for (int i = 0; i < n; i++) {
        val_to_idx[a[i]].push_back(i);
    }

    int ans = 1e9;

    for (auto idxs : val_to_idx) {
        if (idxs.size() < 2) {
            continue;
        }
        for (int i = 0; i < idxs.size() - 1; i++) {
            ans = min(ans, idxs[i + 1] - idxs[i] + 1);
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << '\n';

    return 0;
}