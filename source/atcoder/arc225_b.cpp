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
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> lengths;
        int cur_len = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                cur_len++;
            } else {
                if (cur_len > 0) {
                    lengths.push_back(cur_len);
                    cur_len = 0;
                }
            }
        }
        if (cur_len > 0) {
            lengths.push_back(cur_len);
        }

        int two_cnt = 0;
        for (int i = 0; i < lengths.size(); i++) {
            two_cnt += (lengths[i] == 2);
        }
        if (two_cnt == lengths.size()) {
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    }

    return 0;
}