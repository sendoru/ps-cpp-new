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

    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<int> score(n);
    for (int i = 0; i < m; i++) {
        int cnts[2] = {0, 0};
        for (int j = 0; j < n; j++) {
            cnts[s[j][i] - '0']++;
        }
        if (cnts[0] > cnts[1]) {
            for (int j = 0; j < n; j++) {
                if (s[j][i] == '1') {
                    score[j]++;
                }
            }
        } else {
            for (int j = 0; j < n; j++) {
                if (s[j][i] == '0') {
                    score[j]++;
                }
            }
        }
    }

    int max_score = *max_element(score.begin(), score.end());
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (score[i] == max_score) {
            cout << i + 1 << ' ';
        }
    }

    return 0;
}