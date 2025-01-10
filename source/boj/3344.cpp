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
    list<int> evens, odds;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            evens.push_back(i);
        } else {
            odds.push_back(i);
        }
    }

    if (n % 6 == 2) {
        swap(*odds.begin(), *(++odds.begin()));
        if (n >= 5) {
            odds.erase(next(next(odds.begin())));
            odds.push_back(5);
        }
    } else if (n % 6 == 3) {
        evens.erase(evens.begin());
        evens.push_back(2);
        odds.erase(odds.begin());
        odds.erase(odds.begin());
        odds.push_back(1);
        odds.push_back(3);
    }

    for (auto i : evens) {
        cout << i << ' ';
    }
    for (auto i : odds) {
        cout << i << ' ';
    }

    return 0;
}