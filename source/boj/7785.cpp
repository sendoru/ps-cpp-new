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

    unordered_set<string> m;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name, q;
        cin >> name >> q;
        if (q == "enter") {
            m.insert(name);
        }
        else {
            m.erase(name);
        }
    }

    vector<string> ans;
    for (auto it = m.begin(); it != m.end(); it++) {
        ans.push_back(*it);
    }

    sort(ans.begin(), ans.end(), greater<string>());
    for (auto s : ans) {
        cout << s << '\n';
    }

    return 0;
}