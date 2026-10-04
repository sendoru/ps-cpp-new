// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Event {
    ll x, y, z;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        vector<bool> in_z(2048, false);
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                in_z[i ^ j] = true;
            }
        }
        int z_mex = 0;
        for (int i = 0; i < 2048; i++) {
            if (!in_z[i]) {
                z_mex = i;
                break;
            }
        }

        if (z_mex > c) {
            cout << "No\n";
            continue;
        }

        vector<int> X, Y;
        for (int i = 0; i < a; i++) {
            X.push_back(i);
        }
        X.push_back(1024);
        for (int i = 0; i < b; i++) {
            Y.push_back(i);
        }
        for (int i = 0; i < c; i++) {
            Y.push_back(1024 + i);
        }
        cout << "Yes\n";
        cout << X.size() << " ";
        for (auto x : X) {
            cout << x << " ";
        }
        cout << "\n";
        cout << Y.size() << " ";
        for (auto y : Y) {
            cout << y << " ";
        }
        cout << "\n";
    }

    return 0;
}