// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct RangeUpdatePointQuery {
    int n;
    vector<ll> data;
    vector<ll> lazy;
    RangeUpdatePointQuery(int n) {
        this->n = 1;
        while (this->n < n)
            this->n <<= 1;
        data.assign(2 * this->n, 0);
        lazy.assign(2 * this->n, 0);
    }
    RangeUpdatePointQuery(const vector<ll> &v) {
        n = 1;
        while (n < (int)v.size())
            n <<= 1;
        data.assign(2 * n, 0);
        lazy.assign(2 * n, 0);
        for (int i = 0; i < (int)v.size(); i++) {
            data[n + i] = v[i];
        }
        for (int i = n - 1; i > 0; i--) {
            data[i] = data[2 * i] + data[2 * i + 1];
        }
    }

    void update(int l, int r, ll x) {
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                lazy[l] += x;
                data[l] += x;
                l++;
            }
            if (r & 1) {
                r--;
                lazy[r] += x;
                data[r] += x;
            }
            l >>= 1;
            r >>= 1;
        }
    }

    ll query(int i) {
        i += n;
        ll res = data[i];
        while (i > 1) {
            i >>= 1;
            res += lazy[i];
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<array<ll, 2>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i][0];
            a[i][0]--;
            a[i][1] = i;
        }

        sort(a.begin(), a.end(), greater<>());
        RangeUpdatePointQuery offset(n);

        bool ok = true;
        ll ans = 0;
        priority_queue<array<ll, 2>> pq;
        for (int target = n - 1, i = 0; target >= 0; target--) {
            while (i < n && a[i][0] >= target) {
                pq.push({a[i][1], a[i][0]});
                i++;
            }
            if (pq.empty()) {
                ok = false;
                break;
            }
            auto [pos, val] = pq.top();
            ans += target - (pos + offset.query(pos));
            offset.update(pos + 1, n, -1);
            pq.pop();
        }
        if (ok) {
            cout << ans << "\n";
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}