#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
const ll BUCKET_SIZE = 1000;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
        cin >> i;

    vector<int> aa(n);
    for (int i = 0; i < n; i++) {
        aa[i] += a[i] << 20;
        aa[i] += i;
    }

    for (int i = 0; i < aa.size(); i += BUCKET_SIZE)
        sort(aa.begin() + i, min(aa.begin() + i + BUCKET_SIZE, aa.end()));

    int m;
    cin >> m;
    while (m--) {
        int q;
        cin >> q;
        if (q == 2) {
            int s, e, k;
            cin >> s >> e >> k;
            s--;
            e--;

            auto iter_s = aa.begin() + (s / BUCKET_SIZE * BUCKET_SIZE) + 1,
                 iter_e = min(aa.begin() + ((e + BUCKET_SIZE) / BUCKET_SIZE * BUCKET_SIZE), aa.end());
            int cnt = 0;

            for (auto iter = iter_s; iter < iter_e; iter += BUCKET_SIZE) {
                cnt += min(iter + BUCKET_SIZE, iter_e) - upper_bound(iter, min(iter + BUCKET_SIZE, iter_e), (k << 20) + 2e5);
            }

            for (auto iter = iter_s; iter < min(iter_s + BUCKET_SIZE, aa.end()); iter++) {
                if ((*iter) & ((1 << 20) - 1) < s && ((*iter) >> 20) > k) {
                    cnt--;
                }
            }
            for (auto iter = max(iter_e - BUCKET_SIZE, aa.begin()); iter < iter_e; iter++) {
                if ((*iter) & ((1 << 20) - 1) > e && ((*iter) >> 20) > k) {
                    cnt--;
                }
            }

            cout << cnt << '\n';
        } else {
            int pos, k;
            cin >> pos >> k;
            pos--;
            auto iter_s = aa.begin() + (pos / BUCKET_SIZE * BUCKET_SIZE),
                 iter_e = min(iter_s + BUCKET_SIZE, aa.end());
            for (auto iter = iter_s; iter < iter_e; iter++) {
                if ((*iter) & ((1 << 20) - 1) == pos) {
                    (*iter) = (*iter) & ((1 << 20) - 1);
                    (*iter) += k << 20;
                    break;
                }
            }
            sort(iter_s, iter_e);
        }
    }

    return 0;
}