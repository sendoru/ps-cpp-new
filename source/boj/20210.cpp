// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> order(128, -1);

vector<string> tokenize(const string &s) {
    int n = s.size();
    vector<string> tokens;
    tokens.push_back(s.substr(0, 1));
    for (int i = 1; i < n; i++) {
        if (isdigit(s[i]) && isdigit(s[i - 1])) {
            tokens.back().push_back(s[i]);
        } else {
            tokens.push_back(s.substr(i, 1));
        }
    }
    return tokens;
}

string trim_leading_zeros(const string &s) {
    string res = s;
    reverse(res.begin(), res.end());
    while (res.back() == '0' && res.size() > 1) {
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

bool cmp_token(const string &a, const string &b) {
    bool is_a_num = isdigit(a[0]);
    bool is_b_num = isdigit(b[0]);
    if (is_a_num && is_b_num) {
        string a_trimmed = trim_leading_zeros(a);
        string b_trimmed = trim_leading_zeros(b);
        if (a_trimmed.size() != b_trimmed.size()) {
            return a_trimmed.size() < b_trimmed.size();
        }
        if (a_trimmed != b_trimmed) {
            return a_trimmed < b_trimmed;
        }
        int a_zero_cnt = a.size() - a_trimmed.size();
        int b_zero_cnt = b.size() - b_trimmed.size();
        return a_zero_cnt < b_zero_cnt;
    } else if (is_a_num) {
        return true;
    } else if (is_b_num) {
        return false;
    } else {
        vector<int> a_order(a.size()), b_order(b.size());
        for (int i = 0; i < a.size(); i++) {
            a_order[i] = order[a[i]];
        }
        for (int i = 0; i < b.size(); i++) {
            b_order[i] = order[b[i]];
        }
        return a_order < b_order;
    }
}

bool cmp(const string &a, const string &b) {
    vector<string> a_tokens = tokenize(a);
    vector<string> b_tokens = tokenize(b);
    int an = a_tokens.size();
    int bn = b_tokens.size();
    int n = min(an, bn);
    for (int i = 0; i < n; i++) {
        if (a_tokens[i] != b_tokens[i]) {
            return cmp_token(a_tokens[i], b_tokens[i]);
        }
    }
    return an < bn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (int i = 0; i < 26; i++) {
        order['A' + i] = 2 * i;
        order['a' + i] = 2 * i + 1;
    }

    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    sort(s.begin(), s.end(), cmp);
    for (int i = 0; i < n; i++) {
        cout << s[i] << "\n";
    }

    return 0;
}