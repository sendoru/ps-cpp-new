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

    int n, m;
    cin >> n >> m;
    vector<bool> chosen(1557, false);
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        vector<int> x(l);
        for (int i = 0; i < l; i++) {
            cin >> x[i];
        }
        bool flag = false;
        for (auto elem : x) {
            if (!chosen[elem]) {
                cout << elem << '\n';
                chosen[elem] = true;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << 0 << '\n';
        }
    }

    return 0;
}