// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct solver {
    vector<ll> data;
    int n;
    ll ans = 0;
    solver(const vector<ll> &data) : data(data) {
        n = data.size();
    }
    vector<ll> solve(int l, int r) {
        if (l == r) {
            return {data[l]};
        }
        if (l > r) {
            return {};
        }
        int mid = (l + r) / 2;
        vector<ll> left = solve(l, mid);
        vector<ll> right = solve(mid + 1, r);

        // merge
        vector<ll> merged;
        int i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                merged.push_back(left[i]);
                i++;
            } else {
                merged.push_back(right[j]);
                j++;
                ans += left.size() - i; // count inversions
            }
        }
        while (i < left.size()) {
            merged.push_back(left[i]);
            i++;
        }
        while (j < right.size()) {
            merged.push_back(right[j]);
            j++;
        }
        return merged;
    }

    ll solve() {
        ans = 0;
        solve(0, n - 1);
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> data(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }
    solver s(data);
    cout << s.solve() << "\n";

    return 0;
}