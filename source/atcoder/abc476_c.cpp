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
    vector<int> a;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
        sort(a.begin(), a.end(), greater<int>());
        if (a.size() > 3) {
            a.pop_back();
        }
        if (a.size() == 3) {
            cout << a.back() << '\n';
        }
    }

    return 0;
}