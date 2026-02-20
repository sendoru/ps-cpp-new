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

    string s;
    cin >> s;
    int digit_sum = 0;
    for (char c : s) {
        digit_sum += c - '0';
    }
    if (digit_sum % 3 == 0 && *min_element(s.begin(), s.end()) == '0') {
        sort(s.begin(), s.end(), greater<char>());
        cout << s;
    } else {
        cout << -1;
    }

    return 0;
}