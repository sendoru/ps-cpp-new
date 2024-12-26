// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool validate(vector<vector<int>> &ans)
{
    vector<bool> visited(10001, false);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (ans[i][j] < 1 || ans[i][j] > 10000 || visited[ans[i][j]]) {
                return false;
            }
            visited[ans[i][j]] = true;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int cur = 1;
    vector<vector<int>> ans(100, vector<int>(100, 0));

    for (int r = 1; r < 100; r++) {
        for (int c = 0; c <= r - 1; c++) {
            ans[r][c] = cur++;
        }
    }

    for (int r = 98; r >= 0; r--) {
        for (int c = 99; c >= r + 1; c--) {
            ans[r][c] = cur++;
        }
    }

    for (int i = 0; i < 100; i++) {
        ans[i][i] = cur++;
    }

    if (!validate(ans)) {
        cout << "Invalid" << endl;
        return 0;
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            cout << ans[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}