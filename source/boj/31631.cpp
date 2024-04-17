#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    if (n == 2) {
        cout << "1 2";
        return 0;
    }

    vector<int> ans = {1, 2};
    for (int i = 2; i < n; i++) {
        // sum of current ans is n * (n + 1) / 2
        ll cur_sum = 0;
        for (int j = 0; j < ans.size(); j++) {
            cur_sum += ans[j];
            if (cur_sum <= double(ans.size()) * (ans.size() + 1) / 4 &&
                cur_sum + ans[j + 1] >
                    double(ans.size()) * (ans.size() + 1) / 4) {
                ans.insert(ans.begin() + j + 1, 0);
                break;
            }
        }
        for (int j = 0; j < ans.size(); j++) {
            ans[j] += 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}