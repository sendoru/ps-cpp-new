#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

string conv(string prev, string curr) {
    string ret = curr;
    if (prev.length() < ret.length()) {
        for (int i = 0; i < ret.length(); i++) {
            if (ret[i] == '9') {
                ret[i] = '6';
            }
        }
        return ret;
    }
    // 6 -> 9
    for (int i = 0; i < ret.length(); i++) {
        if (ret[i] == '6') {
            ret[i] = '9';
        }
    }

    // ret >= prev를 유지하면서, ret를 최소화하도록 9 -> 6
    for (int i = 0; i < ret.length(); i++) {
        if (ret[i] == '9') {
            ret[i] = '6';
            if (ret < prev) {
                ret[i] = '9';
            }
        }
    }

    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    bool possible = true;
    v[0] = conv("", v[0]);
    for (int i = 1; i < n; i++) {
        if (v[i].length() < v[i - 1].length()) {
            possible = false;
            break;
        }
        v[i] = conv(v[i - 1], v[i]);
        if (v[i].length() <= v[i - 1].length() && v[i] < v[i - 1]) {
            possible = false;
            break;
        }
    }

    if (possible) {
        cout << "possible\n";
        for (auto s : v) {
            cout << s << '\n';
        }
    } else {
        cout << "impossible\n";
    }

    return 0;
}