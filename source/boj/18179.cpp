// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const string S = "ACGT";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();

    int ans = 0;
    for (char c : S) {
        vector<int> pos1, pos2;
        for (int i = 0; i < n; i++) {
            if (s1[i] == c && s2[i] != c) {
                pos1.push_back(i);
            }
            if (s1[i] != c && s2[i] == c) {
                pos2.push_back(i);
            }
        }
        assert(pos1.size() == pos2.size());
        ans += pos1.size();
        map<char, int> cnt;
        for (int i = 0; i < pos1.size(); i++) {
            cnt[s1[pos2[i]]]++;
            s1[pos2[i]] = c;
            s1[pos1[i]] = '#';
        }
        for (int i = 0; i < pos1.size(); i++) {
            if (cnt.find(s2[pos1[i]]) != cnt.end()) {
                s1[pos1[i]] = s2[pos1[i]];
                cnt[s2[pos1[i]]]--;
                if (cnt[s2[pos1[i]]] == 0) {
                    cnt.erase(s2[pos1[i]]);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (s1[i] == '#') {
                s1[i] = cnt.begin()->first;
                cnt[s1[i]]--;
                if (cnt[s1[i]] == 0) {
                    cnt.erase(s1[i]);
                }
            }
        }
    }

    assert(s1 == s2);
    cout << ans << "\n";

    return 0;
}