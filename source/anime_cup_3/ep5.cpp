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
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 13);

    int k;
    for (int i = 0; i < 14; i++) {
        cin >> k;
        int randint = dis(gen);
        cout << randint << ' ' << 0 << endl;
    }
    cin >> k;
    cout << "1 1" << endl;
    cin >> k;
    cout << "12 0" << endl;
    while (true) {
        cin >> k;
        if (k == -1) {
            break;
        }
        cout << 14 - k << ' ' << 0 << endl;
    }

    return 0;
}