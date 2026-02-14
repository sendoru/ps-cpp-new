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
    vector<string> s(n);
    int max_len = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        max_len = max(max_len, (int)s[i].size());
    }

    for (int i = 0; i < n; i++) {
        int len = s[i].size();
        int diff = max_len - len;
        for (int j = 0; j < diff / 2; j++) {
            cout << '.';
        }
        cout << s[i];
        for (int j = 0; j < diff / 2; j++) {
            cout << '.';
        }
        cout << '\n';
    }

    return 0;
}