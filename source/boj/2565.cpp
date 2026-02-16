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

    int n;
    cin >> n;
    vector<pii> wires(n);
    for (int i = 0; i < n; i++) {
        cin >> wires[i].first >> wires[i].second;
    }
    sort(wires.begin(), wires.end());

    vector<int> lis_stack;
    for (int i = 0; i < n; i++) {
        auto iter = upper_bound(lis_stack.begin(), lis_stack.end(), wires[i].second);
        if (iter == lis_stack.end()) {
            lis_stack.push_back(wires[i].second);
        } else {
            *iter = wires[i].second;
        }
    }
    cout << n - (int)lis_stack.size();

    return 0;
}