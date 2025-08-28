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

    vector<int> grundy(n + 1);
    grundy[0] = grundy[1] = 0;
    grundy[2] = grundy[3] = 1;
    for (int i = 4; i <= n; i++) {
        set<int> s;
        for (int j = 0; i - j - 2 >= 0; j++) {
            s.insert(grundy[j] ^ grundy[i - j - 2]);
        }
        while (s.count(grundy[i])) {
            grundy[i]++;
        }
    }

    cout << (grundy[n] ? 1 : 2) << "\n";

    return 0;
}