// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_failure(const vector<int>& v) {
    int n = v.size();
    vector<int> fail(n, 0);

    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && v[i] != v[j]) {
            j = fail[j - 1];
        }
        if (v[i] == v[j]) {
            j++;
            fail[i] = j;
        }
    }

    return fail;
}

vector<int> kmp_search(const vector<int>& s, const vector<int>& v) {
    vector<int> fail = get_failure(v);
    vector<int> res;

    for (int i = 0, j = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != v[j]) {
            j = fail[j - 1];
        }
        if (s[i] == v[j]) {
            if (j == v.size() - 1) {
                res.push_back(i - v.size() + 1);
                j = fail[j];
            }
            else {
                j++;
            }
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    reverse(v.begin(), v.end());

    vector<int> fail = get_failure(v);
    int max_fail = *max_element(fail.begin(), fail.end());
    int cnt = count(fail.begin(), fail.end(), max_fail);
    if (max_fail == 0) {
        cout << -1;
    }
    else {
        cout << max_fail << ' ' << cnt;
    }

    return 0;
}