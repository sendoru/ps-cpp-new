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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> lengths(n - 1), starts(n - 1), ends(n - 1);
        lengths[0] = 1;
        starts[0] = 0;
        for (int i = 1; i < n; i++) {
            if (i != n - 1 && s[i] == s[i - 1]) {
                lengths[i] = lengths[i - 1] + 1;
                starts[i] = starts[i - 1];
            } else {
                if (i != n - 1) {
                    starts[i] = i;
                    lengths[i] = 1;
                }
                ends[i - 1] = i;
                for (int j = i - 2; j >= 0; j--) {
                    if (j + 1 < n - 1 && s[j] == s[j + 1]) {
                        lengths[j] = lengths[j + 1];
                        ends[j] = ends[j + 1];
                    } else {
                        break;
                    }
                }
            }
        }
        vector<int> imos(n + 10);
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                if (s[i] == 'R') {
                    imos[0]++;
                    imos[n - lengths[0]]--;
                } else {
                    imos[lengths[0]]++;
                    imos[n]--;
                }
            } else if (i == n - 1) {
                if (s[i - 1] == 'R') {
                    imos[lengths[n - 2]]++;
                    imos[n]--;
                } else {
                    imos[0]++;
                    imos[n - lengths[n - 2]]--;
                }
            } else {
                if (s[i - 1] == 'R' && s[i] == 'R') {
                    int left_r_cnt = i - starts[i - 1];
                    int right_r_cnt = ends[i] - i;
                    imos[left_r_cnt]++;
                    imos[n - right_r_cnt]--;
                } else if (s[i - 1] == 'L' && s[i] == 'L') {
                    int left_l_cnt = i - starts[i - 1];
                    int right_l_cnt = ends[i] - i;
                    imos[right_l_cnt]++;
                    imos[n - left_l_cnt]--;
                } else if (s[i - 1] == 'R' && s[i] == 'L') {
                    int cnt = lengths[i - 1] + lengths[i];
                    imos[cnt]++;
                    imos[n]--;
                } else {
                    int cnt = lengths[i - 1] + lengths[i];
                    imos[0]++;
                    imos[n - cnt]--;
                }
            }
        }
        for (int i = 1; i < n; i++) {
            imos[i] += imos[i - 1];
        }
        for (int i = 0; i < n; i++) {
            cout << imos[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}