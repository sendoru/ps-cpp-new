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

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    set<int> nonzero_idxs;
    int cur_xor;
    while (q--) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int x;
            cin >> x;
            if (a[x] == 0) {
                nonzero_idxs.insert(x);
            }
            cur_xor ^= a[x];
            a[x]++;
            cur_xor ^= a[x];
        } else {
            vector<int> zero_idxs;
            for (auto x : nonzero_idxs) {
                cur_xor ^= a[x];
                a[x]--;
                cur_xor ^= a[x];
                if (a[x] == 0) {
                    zero_idxs.push_back(x);
                }
            }
            for (auto x : zero_idxs) {
                nonzero_idxs.erase(x);
            }
        }

        cout << cur_xor << '\n';
    }

    return 0;
}