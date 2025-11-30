// #include "atcoder/all"
#pragma GCC optimize("O3")
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
        int n, m;
        cin >> n >> m;
        vector<int> x(n), y(m);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> y[i];
        }

        bool swapped = false;
        if (n > m) {
            swap(n, m);
            swap(x, y);
            swapped = true;
        }

        auto x_sorted = x;
        auto y_sorted = y;
        sort(x_sorted.begin(), x_sorted.end());
        x_sorted.erase(unique(x_sorted.begin(), x_sorted.end()), x_sorted.end());
        sort(y_sorted.begin(), y_sorted.end());
        y_sorted.erase(unique(y_sorted.begin(), y_sorted.end()), y_sorted.end());
        if (x_sorted.size() != x.size() || y_sorted.size() != y.size()) {
            cout << "No\n";
            continue;
        }

        unordered_map<ll, ll> ix, iy;
        for (int i = 0; i < n; i++) {
            ix[x[i]] = i;
        }
        for (int i = 0; i < m; i++) {
            iy[y[i]] = i;
        }
        unordered_set<int> used_row, used_col;
        vector<unordered_set<int>> empty_col_by_row(n), empty_row_by_col(m);
        vector<unordered_set<int>> used_and_empty_col_by_row(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                empty_col_by_row[i].insert(j);
            }
        }
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                empty_row_by_col[j].insert(i);
            }
        }

        vector<vector<int>> ans(n, vector<int>(m, 0));
        bool valid = true;
        for (int i = n * m; i >= 1; i--) {
            int r, c;
            if (ix.count(i) && iy.count(i)) {
                r = ix[i];
                c = iy[i];
                ans[r][c] = i;
            } else if (ix.count(i)) {
                r = ix[i];
                if (used_and_empty_col_by_row[r].empty()) {
                    valid = false;
                    break;
                }
                c = *used_and_empty_col_by_row[r].begin();
                ans[r][c] = i;
            } else if (iy.count(i)) {
                if (used_row.empty()) {
                    valid = false;
                    break;
                }
                c = iy[i];
                auto itr = used_row.begin();
                r = *itr;
                while (!(used_row.count(r) && empty_row_by_col[c].count(r))) {
                    itr++;
                    if (itr == used_row.end()) {
                        valid = false;
                        break;
                    }
                    r = *itr;
                }
                if (!valid) {
                    break;
                }
                ans[r][c] = i;
            } else {
                if (used_row.empty() || used_col.empty()) {
                    valid = false;
                    break;
                }
                auto itr = used_row.begin();
                r = *itr;
                while (used_and_empty_col_by_row[r].empty()) {
                    itr++;
                    if (itr == used_row.end()) {
                        valid = false;
                        break;
                    }
                    r = *itr;
                }
                if (!valid) {
                    break;
                }
                c = *used_and_empty_col_by_row[r].begin();
                ans[r][c] = i;
            }
            used_row.insert(r);
            used_col.insert(c);
            empty_col_by_row[r].erase(c);
            empty_row_by_col[c].erase(r);
            used_and_empty_col_by_row[r].erase(c);
            for (int r = 0; r < n; r++) {
                if (empty_col_by_row[r].count(c)) {
                    used_and_empty_col_by_row[r].insert(c);
                }
            }
        }
        if (!valid) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        if (swapped) {
            for (int j = 0; j < m; j++) {
                for (int i = 0; i < n; i++) {
                    cout << ans[i][j] << " ";
                }
                cout << "\n";
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }

    return 0;
}