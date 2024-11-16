#include "atcoder/all"
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

    string s;
    cin >> s;
    vector<int> ans;
    int cur = 0;
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == '-') {
            cur++;
        }
        else {
            ans.push_back(cur);
            cur = 0;
        }
    }

    for (auto elem : ans) {
        cout << elem << " ";
    }

    return 0;
}