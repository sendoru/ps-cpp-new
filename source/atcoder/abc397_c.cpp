// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> unique_cnt(n, 0), unique_cnt_rev(n, 0);
    vector<int> cnt(n, 0);
    unique_cnt[0] = 1;
    cnt[a[0]] = 1;
    for (int i = 1; i < n; i++) {
        if (cnt[a[i]] == 0) {
            unique_cnt[i] = unique_cnt[i - 1] + 1;
        }
        else {
            unique_cnt[i] = unique_cnt[i - 1];
        }
        cnt[a[i]]++;
    }

    fill(cnt.begin(), cnt.end(), 0);
    unique_cnt_rev[n - 1] = 1;
    cnt[a[n - 1]] = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (cnt[a[i]] == 0) {
            unique_cnt_rev[i] = unique_cnt_rev[i + 1] + 1;
        }
        else {
            unique_cnt_rev[i] = unique_cnt_rev[i + 1];
        }
        cnt[a[i]]++;
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = max(ans, unique_cnt[i] + unique_cnt_rev[i + 1]);
    }

    cout << ans;

    return 0;
}