#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> lis_stack;
    lis_stack.push_back(0);
    vector<int> prev(n, -1);
    for (int i = 1; i < n; i++) {
        auto iter = upper_bound(
            lis_stack.begin(),
            lis_stack.end(),
            i,
            [&](int a, int b) -> bool { return v[a] < v[b]; });
        if (iter == lis_stack.end()) {
            lis_stack.push_back(i);
            prev[i] = *(lis_stack.end() - 2);
        } else {
            *iter = i;
            if (iter == lis_stack.begin()) {
                prev[i] = -1;
            } else {
                prev[i] = *(iter - 1);
            }
        }
    }

    if (v.size() - lis_stack.size() > 3) {
        cout << "NO\n";
        return 0;
    }

    vector<bool> in_lis(n);
    int cur = lis_stack.back();
    while (cur != -1) {
        in_lis[cur] = true;
        cur = prev[cur];
    }
    cout << "YES\n";
    cout << v.size() - lis_stack.size() << '\n';
    for (int i = 0; i < n; i++) {
        if (!in_lis[i]) {
            if (i == 0) {
                cout << "1 1\n";
                v[0] = 1;
            } else {
                cout << i + 1 << ' ' << v[i - 1] << '\n';
                v[i] = v[i - 1];
            }
        }
    }

    return 0;
}