// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> redo(vector<int> a, vector<int> &ans, int k) {
    for (int i = 0; i < ans.size(); i++) {
        swap(a[ans[i]], a[ans[i] + 1]);
        a[ans[i]] += k;
    }

    return a;
}

bool check(vector<int> a, vector<int> ans, int k) {
    a = redo(a, ans, k);

    for (int i = 0; i < a.size() - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }

    return true;
}

vector<int> solve(vector<int> a, int k) {
    if (a.size() == 1) {
        return {};
    }

    int n = a.size();
    vector<int> ans;
    for (int i = a.size() % 2; i < n; i += 2) {
        int cnt = 0;
        while (a[i] > a[i + 1] || (i != 0 && a[i - 1] > a[i])) {
            ans.push_back(i);
            swap(a[i], a[i + 1]);
            a[i] += k;
            cnt++;
            if (cnt > 3 &&
                i + 2 < n &&
                (i == 0 || (a[i - 1] < a[i] && a[i - 1] < a[i + 1]))) {
                ans.push_back(i + 1);
                swap(a[i + 1], a[i + 2]);
                a[i + 1] += k;
                ans.push_back(i + 1);
                swap(a[i + 1], a[i + 2]);
                a[i + 1] += k;
                break;
            } else if (cnt > 3 &&
                       i != 0 &&
                       (a[i - 1] + 3 * k < a[i] && a[i - 1] + 3 * k < a[i + 1])) {
                ans.push_back(i - 1);
                swap(a[i - 1], a[i]);
                a[i - 1] += k;
                ans.push_back(i - 1);
                swap(a[i - 1], a[i]);
                a[i - 1] += k;
                ans.push_back(i - 1);
                swap(a[i - 1], a[i]);
                a[i - 1] += k;
                ans.push_back(i - 1);
                swap(a[i - 1], a[i]);
                a[i - 1] += k;
                ans.push_back(i);
                swap(a[i], a[i + 1]);
                a[i] += k;
                break;
            } else if (cnt > 3 && a.size() == 2) {
                return {-1};
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    int t = 100;
    while (t--) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis_n(3, 50), dis_k(1, 50), dis_a(1, 50);
        int n = dis_n(gen), k = dis_k(gen);
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = dis_a(gen);
        }

        auto ans = solve(a, k);
        auto recon = redo(a, ans, k);
        if (!is_sorted(recon.begin(), recon.end())) {
            cout << "No" << '\n';
            cout << n << " " << k << '\n';
            for (int i = 0; i < a.size(); i++) {
                cout << a[i] << " ";
            }
            cout << '\n';
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i] << " ";
            }
            cout << '\n';
            for (int i = 0; i < recon.size(); i++) {
                cout << recon[i] << " ";
            }
            cout << '\n';
            break;
        }
    }

    cout << "Done" << '\n';
#else

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto ans = solve(a, k);

    if (ans == vector<int>{-1}) {
        cout << "No" << '\n';
        return 0;
    }

    cout << "Yes" << '\n';
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << " ";
    }
#endif

    return 0;
}