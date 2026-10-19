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

    vector<string> s(2);
    cin >> s[0] >> s[1];

    pii a, d;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (s[i][j] == 'A') {
                a = {i, j};
            } else if (s[i][j] == 'D') {
                d = {i, j};
            }
        }
    }

    cout << (abs(a.first - d.first) + abs(a.second - d.second) == 1 ? "Yes" : "No") << endl;

    return 0;
}