// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int get_dist(const vector<int> &cnt1, const vector<int> &cnt2) {
    int dist = 0;
    for (int i = 0; i < cnt1.size(); i++) {
        dist += abs(cnt1[i] - cnt2[i]);
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    vector<int> cnt(26, 0);
    for (int i = 0; i < s.size(); i++) {
        cnt[s[i] - 'a']++;
    }

    int n;
    cin >> n;
    while (n--) {
        string t;
        cin >> t;
        if (t.size() < s.size()) {
            cout << "NO\n";
            continue;
        }
        vector<int> cnt_t(26, 0);

        if (t.size() == s.size()) {
            for (int i = 0; i < t.size(); i++) {
                cnt_t[t[i] - 'a']++;
            }
            if (get_dist(cnt, cnt_t) == 2) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            continue;
        }

        for (int i = 0; i < s.size(); i++) {
            cnt_t[t[i] - 'a']++;
        }
        if (get_dist(cnt, cnt_t) <= 2) {
            cout << "YES\n";
            continue;
        }
        bool found = false;
        for (int i = s.size(); i < t.size(); i++) {
            cnt_t[t[i] - 'a']++;
            cnt_t[t[i - s.size()] - 'a']--;
            if (get_dist(cnt, cnt_t) <= 2) {
                found = true;
                break;
            }
        }
        cout << (found ? "YES" : "NO") << "\n";
    }

    return 0;
}