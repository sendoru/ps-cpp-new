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
    vector<pii> queries(q);
    set<int> uncovered;
    for (int i = 1; i <= n; i++) {
        uncovered.insert(i);
    }
    vector<int> is_covered(n + 1, 0);
    for (int i = 0; i < q; i++) {
        int qt;
        cin >> qt;
        if (qt == 1) {
            int x;
            cin >> x;
            if (is_covered[x]) {
                uncovered.insert(x);
            }
            else {
                uncovered.erase(x);
            }
            is_covered[x] ^= 1;
            queries[i] = {qt, x};
        }
        else {
            char c;
            cin >> c;
            queries[i] = {qt, c};
        }
    }

    vector<int> is_painted(n + 1, 0);
    string ans(n + 1, 'a');
    for (int i = q - 1; i >= 0; i--) {
        int qt = queries[i].first;
        if (qt == 1) {
            int x = queries[i].second;
            if (is_painted[x]) {
                continue;
            }
            if (is_covered[x]) {
                uncovered.insert(x);
            }
            else {
                uncovered.erase(x);
            }
            is_covered[x] ^= 1;
        }
        else {
            char c = queries[i].second;
            for (int x : uncovered) {
                if (!is_painted[x]) {
                    ans[x] = c;
                    is_painted[x] = 1;
                }
            }
            uncovered.clear();
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i];
    }

    return 0;
}