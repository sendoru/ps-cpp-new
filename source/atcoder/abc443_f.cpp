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

    ll n;
    cin >> n;
    if (n < 10) {
        cout << n;
        return 0;
    } else if (n % 10 == 0) {
        cout << -1;
        return 0;
    }

    vector<int> parents(10 * n, -1);
    queue<ll> q;
    for (ll i = 1; i < 10; i++) {
        ll r = i % n;
        ll node = 10 * r + i;
        q.push(node);
        parents[node] = 0;
    }

    while (!q.empty()) {
        ll node = q.front();
        q.pop();
        ll r = node / 10;
        int d = node % 10;
        for (int nd = d; nd < 10; nd++) {
            ll nr = (r * 10 + nd) % n;
            ll nnode = 10 * nr + nd;
            if (parents[nnode] == -1) {
                parents[nnode] = node;
                if (nr == 0) {
                    vector<int> digits;
                    while (nnode != 0) {
                        digits.push_back(nnode % 10);
                        nnode = parents[nnode];
                    }
                    reverse(digits.begin(), digits.end());
                    for (int digit : digits) {
                        cout << digit;
                    }
                    return 0;
                }
                q.push(nnode);
            }
        }
    }

    cout << -1;

    return 0;
}