#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct compare {
    bool operator()(const pii &a, const pii &b) const {
        int sum_a = a.first + a.second;
        int sum_b = b.first + b.second;
        if (sum_a != sum_b) {
            return sum_a < sum_b;
        }
        return a.first < b.first;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<pii> v;
    for (int i = 1; i < 200; i++) {
        for (int j = i; j < 200; j++) {
            int b = j * j - i * i;
            int a = 2 * i * j;
            if (__gcd(a, b) == 1) {
                v.push_back({min(a, b), max(a, b)});
            }
        }
    }

    sort(v.begin(), v.end(), compare());
    vector<int> prefix_sum(v.size());

    for (int i = 0; i < v.size(); i++) {
        prefix_sum[i] = v[i].first + v[i].second;
        if (i > 0) {
            prefix_sum[i] += prefix_sum[i - 1];
        }
    }

    for (int i = 0; i < prefix_sum.size(); i++) {
        prefix_sum[i] *= 2;
    }

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        auto it = upper_bound(prefix_sum.begin(), prefix_sum.end(), n);
        int idx = it - prefix_sum.begin();
        cout << idx << '\n';
    }

    return 0;
}