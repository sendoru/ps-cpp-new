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
    vector<array<ll, 2>> hl(n);
    multiset<ll> h;
    for (int i = 0; i < n; i++) {
        cin >> hl[i][0] >> hl[i][1];
        h.insert(hl[i][0]);
    }

    sort(hl.begin(), hl.end(), [](const array<ll, 2> &a, const array<ll, 2> &b) {
        return a[1] < b[1];
    });

    int q;
    cin >> q;
    vector<ll> ans(q);
    vector<array<ll, 2>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i][0];
        queries[i][1] = i;
    }
    sort(queries.begin(), queries.end());
    int idx = 0;
    for (int i = 0; i < q; i++) {
        while (idx < n && hl[idx][1] <= queries[i][0]) {
            h.erase(h.find(hl[idx][0]));
            idx++;
        }
        if (h.empty()) {
            // this shouldn't happen though
            ans[queries[i][1]] = -1;
        } else {
            ans[queries[i][1]] = *h.rbegin();
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}

/*
329
329
329
755
755
755
755
329
755
329
329
329
755
772

329
329
329
755
755
755
755
329
755
329
329
329
755
772
*/