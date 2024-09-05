#include "atcoder/all"
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

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<int> perm(s.size());
        iota(perm.begin(), perm.end(), 0);
        cout << "Case # " << i + 1 << ":\n";
        cout << s << '\n';
        while (next_permutation(perm.begin(), perm.end())) {
            for (int i = 0; i < perm.size(); i++) {
                cout << s[perm[i]];
            }
            cout << '\n';
        }
    }

    return 0;
}