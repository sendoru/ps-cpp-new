#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool is_end_points(vector<int> &a, vector<int> &b) {
    int d = a.size();
    for (int i = 0; i < d; i++) {
        int diff = a[i] - b[i];
        if (diff != 0 && diff != -4 && diff != 4) {
            return false;
        }
    }

    return true;
}

pair<int, vector<int>> get_line(vector<int> &a, vector<int> &b) {
    int d = a.size();
    int gcd = 0;
    for (int i = 0; i < d; i++) {
        int diff = a[i] - b[i];
        gcd = __gcd(gcd, diff);
    }
    vector<int> ret;
    for (int i = 0; i < d; i++) {
        int diff = a[i] - b[i];
        diff /= gcd;
        ret.push_back(diff);
        if (abs(diff) > 1) {
            return {MOD1, {MOD1}};
        }
    }

    return {gcd, ret};
}

bool is_connected(vector<int> &a, vector<int> &b, set<vector<int>> &s) {
    int d = a.size();
    vector<int> mid(d);
    for (int i = 0; i < d; i++) {
        mid[i] = (a[i] + b[i]) / 2;
    }
    if (s.find(mid) == s.end()) {
        return false;
    }
    vector<int> left(d);
    for (int i = 0; i < d; i++) {
        left[i] = (a[i] + mid[i]) / 2;
    }
    if (s.find(left) == s.end()) {
        return false;
    }
    vector<int> right(d);
    for (int i = 0; i < d; i++) {
        right[i] = (b[i] + mid[i]) / 2;
    }
    if (s.find(right) == s.end()) {
        return false;
    }

    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int d, n;
    cin >> d >> n;
    set<vector<int>> s;
    for (int i = 0; i < n; i++) {
        vector<int> cur(d);
        for (int j = 0; j < d; j++) {
            cin >> cur[j];
        }
        s.insert(cur);
        for (auto it = s.begin(); it != s.end(); it++) {
            auto other = *it;
            if (other == cur) {
                continue;
            }
            auto dir = get_line(cur, other);
            if (dir.second[0] == MOD1 || dir.first >= 2) {
                continue;
            }
            for (int start = 1; start <= 4; start++) {
                vector<int> a = cur;
                vector<int> b = cur;
                for (int j = 0; j < d; j++) {
                    a[j] -= start * dir.second[j];
                    b[j] += (4 - start) * dir.second[j];
                }
                if (s.find(a) != s.end() && s.find(b) != s.end() && is_connected(a, b, s)) {
                    cout << i + 1;
                    return 0;
                }
            }
        }
    }

    cout << "NOT ALIGNED\n";

    return 0;
}