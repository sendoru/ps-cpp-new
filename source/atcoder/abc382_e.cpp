// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

double geq_sum(vector<double> &prefix_sum, int l) {
    if (l >= prefix_sum.size()) {
        return 0;
    }
    if (l == 0) {
        return 1;
    }
    return 1 - prefix_sum[l - 1];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i] /= 100;
    }

    vector<double> pmf_of_single_pack(n + 1);
    pmf_of_single_pack[0] = 1;
    for (int i = 0; i < n; i++) {
        vector<double> next_pmf(n + 1);
        for (int j = 0; j <= i; j++) {
            next_pmf[j] += pmf_of_single_pack[j] * (1 - p[i]);
            next_pmf[j + 1] += pmf_of_single_pack[j] * p[i];
        }
        swap(pmf_of_single_pack, next_pmf);
    }

    // TODO

    cout << fixed << setprecision(10) << dp2[x] << endl;

    return 0;
}