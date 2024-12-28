// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k;
    cin >> k;
    string s, t;
    cin >> s >> t;

    if (s == t) {
        cout << "Yes" << endl;
        return 0;
    }

    if (abs((int)s.length() - (int)t.length()) > 2) {
        cout << "No" << endl;
        return 0;
    }

    if (s.length() == t.length()) {
        int diff = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != t[i]) {
                diff++;
            }
        }
        if (diff <= 1) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }

    else {
        if (s.length() < t.length()) {
            swap(s, t);
        }
        t.push_back('$');
        int diff = 0;
        for (int i = 0, j = 0; i < s.length() && j < t.length(); i++, j++) {
            if (s[i] != t[j]) {
                diff++;
                if (diff > 1) {
                    cout << "No" << endl;
                    return 0;
                }
                j--;
            }
        }

        cout << "Yes" << endl;
    }
    return 0;
}