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
    priority_queue<int, vector<int>, greater<int>> pq;
    while (q--) {
        int t, h;
        cin >> t >> h;
        if (t == 1) {
            pq.push(h);
        } else {
            while (!pq.empty() && pq.top() <= h) {
                pq.pop();
            }
        }
        cout << pq.size() << '\n';
    }

    return 0;
}