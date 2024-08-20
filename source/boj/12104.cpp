#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_failure(string &s) {
    int n = s.size();
    vector<int> failure(n, 0);
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) {
            j = failure[j - 1];
        }
        if (s[i] == s[j]) {
            failure[i] = ++j;
        }
    }
    return failure;
}

// return set of i such that s[i:i+p.size()] == p
vector<int> kmp(string &s, string &p) {
    vector<int> failure = get_failure(p);
    vector<int> ret;
    for (int i = 0, j = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != p[j]) {
            j = failure[j - 1];
        }
        if (s[i] == p[j]) {
            if (j == p.size() - 1) {
                ret.push_back(i - p.size() + 1);
                j = failure[j];
            } else {
                j++;
            }
        }
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s, p;
    cin >> s >> p;
    s += s;
    s.pop_back();
    vector<int> ret = kmp(s, p);
    cout << ret.size() << '\n';

    return 0;
}