// #include "atcoder/all"
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
    // initialize random seed with cpu time
    mt19937 gen(random_device{}());

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<string> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }

        string ans;
        bool solved = false;
        for (char c = 'A'; c <= 'Z'; c++) {
            ans += c;
        }
        for (int i = 0; i < 10000; i++) {
            bool ok = true;
            for (int j = 0; j < n; j++) {
                if (ans.find(p[j]) != string::npos) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << "Case #" << t << ": " << ans << '\n';
                solved = true;
                break;
            }
            shuffle(ans.begin(), ans.end(), gen);
        }
        if (!solved) {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        }
    }

    return 0;
}