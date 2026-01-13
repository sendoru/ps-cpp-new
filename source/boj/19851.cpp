// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const int BUCKET_SIZE = 1000;

vector<int> v(1'000'010, 0);
vector<int> bucket_sum(1001, 0);
vector<int> bucket_pf_min(1001, 0);
vector<int> bucket_pf_max(1001, 0);
vector<int> bucket_sign(1001, 1); // 1 or -1

void update_partial_bucket(int l, int r) {
    for (int i = l; i <= r; i++) {
        v[i] *= -1;
    }
    int pf = 0;
    int b = l / BUCKET_SIZE;
    bucket_sum[b] = 0;
    bucket_pf_min[b] = 0;
    bucket_pf_max[b] = 0;
    for (int i = b * BUCKET_SIZE; i < min((b + 1) * BUCKET_SIZE, (int)v.size()); i++) {
        bucket_sum[b] += v[i] * bucket_sign[b];
        pf += v[i] * bucket_sign[b];
        bucket_pf_min[b] = min(bucket_pf_min[b], pf);
        bucket_pf_max[b] = max(bucket_pf_max[b], pf);
    }
}

// min prefix sum in [l, r], total sum in [l, r]
pii get_partial_bucket_info(int l, int r) {
    int pf = 0;
    int min_pf = 0;
    for (int i = l; i <= r; i++) {
        pf += v[i] * bucket_sign[l / BUCKET_SIZE];
        min_pf = min(min_pf, pf);
    }
    return {min_pf, pf};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            v[i] = 1;
        } else {
            v[i] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        bucket_sum[i / BUCKET_SIZE] += v[i];
    }
    for (int i = 0; i < n; i++) {
        int pf = 0;
        for (int j = (i / BUCKET_SIZE) * BUCKET_SIZE; j <= i; j++) {
            pf += v[j];
        }
        bucket_pf_min[i / BUCKET_SIZE] = min(bucket_pf_min[i / BUCKET_SIZE], pf);
        bucket_pf_max[i / BUCKET_SIZE] = max(bucket_pf_max[i / BUCKET_SIZE], pf);
    }

    int q;
    cin >> q;
    while (q--) {
        int qt;
        cin >> qt;
        // *-1 for [l, r]
        if (qt == 1) {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            int l_bucket = l / BUCKET_SIZE;
            int r_bucket = r / BUCKET_SIZE;
            if (l_bucket == r_bucket) {
                // same bucket
                update_partial_bucket(l, r);
            } else {
                // left partial bucket
                update_partial_bucket(l, (l_bucket + 1) * BUCKET_SIZE - 1);
                // middle full buckets
                for (int i = l_bucket + 1; i < r_bucket; i++) {
                    bucket_sum[i] *= -1;
                    int old_min = bucket_pf_min[i];
                    int old_max = bucket_pf_max[i];
                    bucket_pf_min[i] = -old_max;
                    bucket_pf_max[i] = -old_min;
                    bucket_sign[i] *= -1;
                }
                // right partial bucket
                update_partial_bucket(r_bucket * BUCKET_SIZE, r);
            }
        } else if (qt == 2) {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            // min prefix sum
            int total_sum = 0;
            int min_pf = 0;
            int l_bucket = l / BUCKET_SIZE;
            int r_bucket = r / BUCKET_SIZE;
            if (l_bucket == r_bucket) {
                // same bucket
                pii res = get_partial_bucket_info(l, r);
                min_pf = res.first;
                total_sum = res.second;
            } else {
                // left partial bucket
                pii res = get_partial_bucket_info(l, (l_bucket + 1) * BUCKET_SIZE - 1);
                min_pf = res.first;
                total_sum = res.second;
                // middle full buckets
                for (int i = l_bucket + 1; i < r_bucket; i++) {
                    min_pf = min(min_pf, total_sum + bucket_pf_min[i]);
                    total_sum += bucket_sum[i];
                }
                // right partial bucket
                res = get_partial_bucket_info(r_bucket * BUCKET_SIZE, r);
                min_pf = min(min_pf, total_sum + res.first);
                total_sum += res.second;
            }
            cout << (r - l + 1) + total_sum - 2 * min_pf << '\n';
        }
    }

    return 0;
}
