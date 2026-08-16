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
    string s;
    cin >> s;
    int period = n;
    for (int i = 1; i <= n; i++) {
        if (n % i != 0) {
            continue;
        }
        string sub = s.substr(0, i);
        bool valid = true;
        for (int j = 0; j < n; j += i) {
            if (s.substr(j, i) != sub) {
                valid = false;
                break;
            }
        }
        if (valid) {
            period = i;
            break;
        }
    }

    cout << n / period << "\n";
    cout << s.size() * s.size() << "\n";
    for (int i = 0; i < s.size(); i++) {
        cout << s;
    }

    return 0;
}