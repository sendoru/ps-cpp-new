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
        vector<int> v(26, 0);
        for (char c : s) {
            if (c >= 'a' && c <= 'z') {
                v[c - 'a']++;
            } else if (c >= 'A' && c <= 'Z') {
                v[c - 'A']++;
            } else {
                continue;
            }
        }

        bool flag = true;
        for (int i = 0; i < 13; i++) {
            if (v[i] != v[25 - i]) {
                flag = false;
                break;
            }
        }

        cout << (flag ? "Yes" : "No") << '\n';
    }

    return 0;
}