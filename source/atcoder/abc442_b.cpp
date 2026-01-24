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

    int q;
    cin >> q;

    bool playing = false;
    int volume = 0;
    while (q--) {
        int a;
        cin >> a;
        if (a == 1) {
            volume++;
        } else if (a == 2) {
            volume = max(0, volume - 1);
        } else {
            playing = !playing;
        }
        bool ans = playing && volume >= 3;
        cout << (ans ? "Yes" : "No") << "\n";
    }

    return 0;
}