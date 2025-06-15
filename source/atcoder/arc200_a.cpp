// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll cross(pll a, pll b) {
    return a.first * b.second - a.second * b.first;
}

ll dot(vector<ll> a, vector<ll> b) {
    assert(a.size() == b.size());
    ll res = 0;
    for (int i = 0; i < a.size(); i++) {
        res += a[i] * b[i];
    }
    return res;
}

bool check(vector<ll> &a, vector<ll> &b, vector<ll> &ans) {
    return (dot(a, ans) > 0 && dot(b, ans) < 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        ll possible = false;
        ll pivot;
        for (pivot = 1; pivot < n; pivot++) {
            if (cross({a[0], b[0]}, {a[pivot], b[pivot]}) != 0 || dot({a[0], b[0]}, {a[pivot], b[pivot]}) < 0) {
                possible = true;
                break;
            }
        }

        if (!possible) {
            cout << "No\n";
            continue;
        }

        cout << "Yes\n";

        vector<ll> ans(n);
        if (cross({a[0], b[0]}, {a[pivot], b[pivot]}) == 0) {
            ans[0] = a[0];
            ans[pivot] = a[pivot];
        } else {
            ans[0] = -a[pivot] - b[pivot];
            ans[pivot] = a[0] + b[0];
            if (!check(a, b, ans)) {
                ans[0] *= -1;
                ans[pivot] *= -1;
            }
            assert(check(a, b, ans));
        }

        check(a, b, ans);
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}