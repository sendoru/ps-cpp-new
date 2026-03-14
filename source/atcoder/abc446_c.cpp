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

    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        queue<int> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a[i]; j++) {
                q.push(i);
            }
            for (int j = 0; j < b[i] && !q.empty(); j++) {
                q.pop();
            }
            while (!q.empty() && q.front() <= i - d) {
                q.pop();
            }
        }

        cout << q.size() << '\n';
    }

    return 0;
}