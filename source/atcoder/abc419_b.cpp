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
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v;
            cin >> v;
            pq.push(v);
        } else {
            cout << pq.top() << '\n';
            pq.pop();
        }
    }

    return 0;
}