#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (auto &elem : a) {
        cin >> elem;
        elem--;
    }
    sort(a.begin(), a.end());
    if (a[0] == 0 || a.back() == n - 1) {
        cout << -1;
        return 0;
    }

    vector<vector<int>> chunks;
    for (int i = 0; i < m; i++) {
        if (i == 0) {
            chunks.push_back({a[i]});
        }
        else {
            if (a[i] - a[i - 1] > 1) {
                chunks.push_back({a[i]});
            }
            else {
                chunks.back().push_back(a[i]);
            }
        }
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = i;
    }

    for (auto &chunk : chunks) {
        int chunk_size = chunk.size();
        int chunk_start = chunk[0];
        for (int i = 0; i < chunk_size; i++) {
            ans[chunk_start + i] = chunk[i] + 1;
        }
        ans[chunk_start + chunk_size] = chunk_start;
    }

    for (auto &elem : ans) {
        cout << elem + 1 << " ";
    }

    return 0;
}