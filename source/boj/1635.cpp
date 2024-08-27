#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool test(int n)
{
    vector<vector<int>> v;
    for (int i = 0; i < (1 << n); i++) {
        vector<int> u;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                u.push_back(1);
            }
            else {
                u.push_back(-1);
            }
        }
        v.push_back(u);
    }

    vector<vector<int>> u;
    for (int i = 0; i < n / 2; i++) {
        vector<int> ui(n, 1);
        for (int j = i; j - i < n / 2; j++) {
            ui[j] = -1;
        }
        u.push_back(ui);
        ui = vector<int>(n, 1);
        for (int j = i; j - i < n / 2 - 1; j++) {
            ui[j] = -1;
        }
        u.push_back(ui);
    }

    int m = v.size();

    vector<vector<int>> ans(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < u.size(); j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += u[j][k] * v[i][k];
            }
            if (sum == 0) {
                ans[i] = u[j];
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (ans[i].empty()) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (int i = 4; i <= 14; i += 2) {
        cout << i << " " << test(i) << "\n";
    }
    return 0;
#endif

    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    vector<vector<int>> u;
    for (int i = 0; i < n / 2; i++) {
        vector<int> ui(n, 1);
        for (int j = i; j - i < n / 2; j++) {
            ui[j] = -1;
        }
        u.push_back(ui);
        ui = vector<int>(n, 1);
        for (int j = i; j - i < n / 2 - 1; j++) {
            ui[j] = -1;
        }
        u.push_back(ui);
    }

    vector<vector<int>> ans(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < u.size(); j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += u[j][k] * v[i][k];
            }
            if (sum == 0) {
                ans[i] = u[j];
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}