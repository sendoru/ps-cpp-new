#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int solve(vector<int> &a)
{
    // case -1:
    if (a == vector<int>{3}) {
        return -1;
    }

    int n = a.size();
    vector<vector<int>> pos(4);
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }

    // case 0:
    if (pos[3].size() == 0) {
        return 0;
    }

    // case 1:
    int first_3 = pos[3].front(), last_3 = pos[3].back();
    int xor_sum = 0;
    for (int i = first_3; i <= last_3; i++) {
        xor_sum ^= a[i];
    }
    if (xor_sum != 3) {
        return 1;
    }
    for (auto elem : pos[1]) {
        if (elem < first_3 || elem > last_3) {
            return 1;
        }
    }
    for (auto elem : pos[2]) {
        if (elem < first_3 || elem > last_3) {
            return 1;
        }
    }

    // case 2:
    // if there is a segment that contains all 3s and the length is even, then it is possible to make the xor sum 0 by 2 operations
    if ((last_3 - first_3 + 1) % 2 == 0 || (last_3 - first_3 + 1) < n) {
        return 2;
    }
    // the only case that remains is combination of:
    // 1) xor_sum = 3
    // 2) a.front() == 3 && a.back() == 3
    // 3) a.size() is odd
    xor_sum = a[0];
    for (int i = 1; i < n; i++) {
        xor_sum ^= a[i];
        if (xor_sum == 1 || xor_sum == 2) {
            return 2;
        }
        else if (xor_sum == 3 && (i + 1) % 2 == 0) {
            return 2;
        }
    }

    return 3;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<vector<int>> pos(4);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = solve(a);
        reverse(a.begin(), a.end());
        ans = min(ans, solve(a));
        cout << ans << '\n';
    }

    return 0;
}