#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

map<string, int> points = {
    {"TT", 75},
    {"TX", 50},
    {"PR", 80},
    {"RT", 30},
    {"AP", 25},
    {"PX", 60},
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        int w, n;
        cin >> w >> n;
        if (w == 0) {
            break;
        }

        vector<pair<string, int>> scores(n);
        map<string, int> total;
        for (int i = 0; i < n; i++) {
            string name, code;
            cin >> name >> code;
            int score = points[code];
            scores[i] = {name, score};
            total[name] += score;
        }
        vector<string> ans;
        map<string, bool> marked;
        for (auto [name, score] : scores) {
            if (total[name] >= 100 && !marked[name]) {
                ans.push_back(name);
                marked[name] = true;
            }
        }

        cout << "Week " << w << " ";
        if (ans.empty()) {
            cout << "No phones confiscated\n";
        } else {
            for (int i = 0; i < ans.size(); i++) {
                if (i != ans.size() - 1) {
                    cout << ans[i] << ",";
                } else {
                    cout << ans[i] << "\n";
                }
            }
        }
    }

    return 0;
}