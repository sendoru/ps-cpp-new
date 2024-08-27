#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> add(vector<int> &a, vector<int> &b, vector<int> basis_size)
{
    int n = basis_size.size();
    vector<int> ret(basis_size.size());
    for (int i = n - 1; i >= 0; i--) {
        ret[i] = a[i] + b[i];
        if (ret[i] >= basis_size[i]) {
            ret[i] -= basis_size[i];
            if (i != 0) {
                a[i - 1]++;
            }
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<bool>> used(n, vector<bool>(26));
    vector<string> t(k);
    for (int i = 0; i < k; i++) {
        cin >> t[i];
        for (int j = 0; j < t[i].size(); j++) {
            used[j][t[i][j] - 'a'] = true;
        }
    }

    string a, b;
    cin >> a >> b;

    vector<vector<char>> basis(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (!used[i][j]) {
                basis[i].push_back(j + 'a');
            }
        }
    }

    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        cnt[i] = basis[i].size();
    }

    vector<int> a_conv(n), b_conv(n);
    for (int i = 0; i < n; i++) {
        a_conv[i] = find(basis[i].begin(), basis[i].end(), a[i]) - basis[i].begin();
        b_conv[i] = find(basis[i].begin(), basis[i].end(), b[i]) - basis[i].begin();
    }

    vector<int> ret = add(a_conv, b_conv, cnt);
    string ans;
    for (int i = 0; i < n; i++) {
        ans.push_back(basis[i][ret[i]]);
    }

    cout << ans << '\n';

    return 0;
}