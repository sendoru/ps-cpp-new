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

    int n, q;
    cin >> n >> q;

    vector<int> pigeon_idxs(n);
    iota(pigeon_idxs.begin(), pigeon_idxs.end(), 0);
    vector<int> idx_to_nest(n);
    iota(idx_to_nest.begin(), idx_to_nest.end(), 0);
    vector<int> nest_to_idx(n);
    iota(nest_to_idx.begin(), nest_to_idx.end(), 0);

    while (q--) {
        int op;
        cin >> op;
        int a, b;
        if (op == 1) {
            cin >> a >> b;
            a--;
            b--;
            pigeon_idxs[a] = nest_to_idx[b];
        }
        else if (op == 2) {
            cin >> a >> b;
            a--;
            b--;

            int a_idx = nest_to_idx[a];
            int b_idx = nest_to_idx[b];

            nest_to_idx[a] = b_idx;
            nest_to_idx[b] = a_idx;

            idx_to_nest[a_idx] = b;
            idx_to_nest[b_idx] = a;
        }
        else {
            cin >> a;
            a--;
            cout << idx_to_nest[pigeon_idxs[a]] + 1 << '\n';
        }
    }

    return 0;
}