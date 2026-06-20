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

    int a;
    char b;
    cin >> a >> b;
    b -= 'A';
    for (int i = 0; i < a; i++) {
        string s;
        cin >> s;
        if (s[b] == 'o') {
            cout << "Yes";
            return 0;
        }
    }
    cout << "No";

    return 0;
}