// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// finds if val is unique in v[l, r]
bool is_unique(map<int, vector<int>> &idxs, int val, int l, int r) {
    auto iter_l = lower_bound(idxs[val].begin(), idxs[val].end(), l);
    if (iter_l + 1 == idxs[val].end()) {
        return true;
    }
    return *(iter_l + 1) > r;
}

bool is_non_boring(vector<int> &v, map<int, vector<int>> &idxs, int l, int r) {
    if (l >= r) {
        return true;
    }

    for (int i = 0; l + i <= r - i; i++) {
        int val = v[l + i];
        int pivot = l + i;
        if (is_unique(idxs, val, l, r)) {
            return is_non_boring(v, idxs, l, pivot - 1) && is_non_boring(v, idxs, pivot + 1, r);
        }
        val = v[r - i];
        pivot = r - i;
        if (is_unique(idxs, val, l, r)) {
            return is_non_boring(v, idxs, l, pivot - 1) && is_non_boring(v, idxs, pivot + 1, r);
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        map<int, vector<int>> idxs;
        for (int i = 0; i < n; i++) {
            idxs[v[i]].push_back(i);
        }

        cout << (is_non_boring(v, idxs, 0, n - 1) ? "non-boring" : "boring") << '\n';
    }

    return 0;
}