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

    int n, q;
    cin >> n >> q;

    vector<int> t(q);
    for (int i = 0; i < q; i++) {
        cin >> t[i];
    }

    vector<int> state(n, 1);

    for (int i = 0; i < t.size(); i++) {
        state[t[i] - 1] = (state[t[i] - 1] + 1) % 2;
    }

    int ans = 0;
    for (int i = 0; i < state.size(); i++) {
        ans += state[i];
    }

    cout << ans;

    return 0;
}