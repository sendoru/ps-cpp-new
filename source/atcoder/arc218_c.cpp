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

    cout << "2\n";
    cout << flush;

    vector<int> swap_perm(n), shift_perm(n);
    iota(swap_perm.begin(), swap_perm.end(), 1);
    swap_perm[0] = 2;
    swap_perm[1] = 1;
    iota(shift_perm.begin() + 1, shift_perm.end(), 1);
    shift_perm[0] = n;

    for (int i = 0; i < n; i++) {
        cout << swap_perm[i] << " ";
    }
    cout << "\n";
    cout << flush;
    for (int i = 0; i < n; i++) {
        cout << shift_perm[i] << " ";
    }
    cout << "\n";
    cout << flush;

    deque<int> query_perm(n);
    for (int i = 0; i < n; i++) {
        cin >> query_perm[i];
    }

    // convert everything to 0-indexed
    for (int i = 0; i < n; i++) {
        swap_perm[i]--;
        shift_perm[i]--;
        query_perm[i]--;
    }

    vector<int> query_perm_inv(n);
    for (int i = 0; i < n; i++) {
        query_perm_inv[query_perm[i]] = i;
    }

    vector<int> ans;
    deque<int> cur_perm(n);
    iota(cur_perm.begin(), cur_perm.end(), 0);
    while (cur_perm != query_perm) {
        // swap the first two elements if they are inverted
        if (query_perm_inv[cur_perm[0]] > query_perm_inv[cur_perm[1]]) {
            if (!(query_perm_inv[cur_perm[0]] == n - 1 && query_perm_inv[cur_perm[1]] == 0)) {
                ans.push_back(1);
                swap(cur_perm[0], cur_perm[1]);
            }
            if (cur_perm == query_perm) {
                break;
            }
        }
        // regardless of the first two elements, shift everything else by one
        ans.push_back(2);
        cur_perm.push_front(cur_perm.back());
        cur_perm.pop_back();
    }

    cout << ans.size() << " ";
    for (int i : ans) {
        cout << i << " ";
    }
    cout << "\n";
    cout << flush;

    return 0;
}