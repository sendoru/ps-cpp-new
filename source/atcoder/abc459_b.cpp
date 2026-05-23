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
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    for (int i = 0; i < n; i++) {
        char c = s[i][0];
        int val = 0;
        if (c <= 'c') {
            val = 1;
        } else if (c <= 'f') {
            val = 2;
        } else if (c <= 'i') {
            val = 3;
        } else if (c <= 'l') {
            val = 4;
        } else if (c <= 'o') {
            val = 5;
        } else if (c <= 's') {
            val = 6;
        } else if (c <= 'v') {
            val = 7;
        } else {
            val = 8;
        }
        val++;
        cout << val;
    }

    return 0;
}