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

vector<int> solve(vector<int> &a) {
    int n = a.size() / 2;
    vector<bool> included(n);
    vector<int> cnt(n);
    vector<int> ans;
    bool odd = true;
    included[a[0]] = true;
    cnt[a[0]] = 1;
    for (int i = 1; i < n * 2; i++) {
        if (odd) {
            if (included[a[i]]) {
                odd = false;
                ans.push_back(i);
            } else {
                included[a[i]] = true;
            }
        } else {
            if (cnt[a[i]] == 1 && !included[a[i]]) {
                odd = true;
                included[a[i]] = true;
                ans.push_back(i);
            }
        }
        cnt[a[i]]++;
    }
    return ans;
}

bool check(vector<int> &a, vector<int> &ans) {
    int n = a.size() / 2;
    if (ans.size() > n) {
        return false;
    }
    set<int> ans_set(ans.begin(), ans.end());
    vector<int> cnt(n);
    bool odd = true;
    for (int i = 0; i < 2 * n; i++) {
        if (odd) {
            cnt[a[i]]++;
        }
        if (ans_set.count(i + 1)) {
            odd = !odd;
        }
    }

    for (int i = 0; i < n; i++) {
        if (cnt[i] != 1) {
            return false;
        }
    }

    return true;
}

bool test(int n) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<int> a(n * 2);
    for (int i = 0; i < n * 2; i++) {
        a[i] = i / 2;
    }
    shuffle(a.begin(), a.end(), rng);
    auto ans = solve(a);
    if (!check(a, ans)) {
        cout << "Wrong!" << endl;
        cout << n << endl;
        for (int i = 0; i < n * 2; i++) {
            cout << a[i] + 1 << ' ';
        }
        cout << endl;
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << endl;
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (int n = 1; n <= 100; n++) {
        if (!test(n)) {
            break;
        }
    }
    cout << "All tests passed!" << endl;
#endif

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n * 2);
        for (int i = 0; i < n * 2; i++) {
            cin >> a[i];
            a[i]--;
        }
        auto ans = solve(a);
#ifdef DEBUG
        if (!check(a, ans)) {
            cout << "Wrong!" << endl;
        }
#endif
        cout << ans.size() << '\n';
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}