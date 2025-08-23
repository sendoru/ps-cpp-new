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

    ll n, s;
    cin >> n >> s;
    deque<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int sign = 1;
    ll moved = 0;
    while (!a.empty()) {
        if (sign == 1) {
            moved += 2 * a.back();
            a.pop_back();
        } else {
            moved -= 2 * a.front();
            a.pop_front();
        }
        sign *= -1;
    }

    cout << s * sign + moved;

    return 0;
}