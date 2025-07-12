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

    int n, k;
    cin >> n >> k;
    vector<int> a(k), b(k), unique_elems;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        a[i]--;
        unique_elems.push_back(a[i]);
    }
    for (int i = 0; i < k; i++) {
        cin >> b[i];
        b[i]--;
        unique_elems.push_back(b[i]);
    }
    sort(unique_elems.begin(), unique_elems.end());
    unique_elems.erase(unique(unique_elems.begin(), unique_elems.end()), unique_elems.end());
    vector<int> a_inv(n, -1);
    for (int i = 0; i < k; i++) {
        a_inv[a[i]] = i;
    }
    vector<int> b_new(k, -1);
    for (int i = 0; i < k; i++) {
        b_new[i] = a_inv[b[i]];
    }

    for (int i = 0; i < k; i++) {
        b_new.push_back(b_new[i]);
    }
    int ans = 0;
    vector<int> cnts(11 * (int)1e5);
    for (int i = 0; i < b_new.size(); i++) {
        if (b_new[i] != -1) {
            cnts[b_new[i] + i]++;
            ans = max(ans, cnts[b_new[i] + i]);
        }
    }
    cnts.assign(11 * (int)1e5, 0);
    reverse(b_new.begin(), b_new.end());
    for (int i = 0; i < b_new.size(); i++) {
        if (b_new[i] != -1) {
            cnts[b_new[i] + i]++;
            ans = max(ans, cnts[b_new[i] + i]);
        }
    }

    cout << ans + n - unique_elems.size() << "\n";

    return 0;
}