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

    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    vector<int> replace_idx(n, -1);
    for (char c = '9'; c >= '1'; c--) {
        int i = 0;
        int same_i = -1;
        bool throwable = false;
        for (int j = m - 1; j >= 0; j--) {
            if (t[j] == c) {
                while (i < n && (s[i] >= c || j < replace_idx[i])) {
                    if (j < replace_idx[i]) {
                        throwable = true;
                    }
                    if (s[i] == c) {
                        same_i = i;
                    }
                    i++;
                }
                if (i == n && !throwable) {
                    if (same_i != -1) {
                        s[same_i] = c;
                        replace_idx[same_i] = max(replace_idx[same_i], j);
                    } else {
                        s.back() = c;
                        replace_idx.back() = max(replace_idx.back(), j);
                    }
                } else if (i != n) {
                    s[i] = c;
                    replace_idx[i] = j;
                    i++;
                }
            }
        }
    }

    cout << s << endl;

    return 0;
}