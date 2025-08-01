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

ll solve(vector<int> &a) {
    ll n = a.size();
    map<int, vector<int>> pos;
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }

    ll ans = n * (n - 1) / 2 + 1;
    for (auto &[_, v] : pos) {
        ans -= v.size() * (v.size() - 1) / 2;
    }
    return ans;
}

ll solve_naive(vector<int> &a) {
    set<vector<int>> s = {a};
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            auto b = a;
            reverse(b.begin() + i, b.begin() + j + 1);
            s.insert(b);
        }
    }
    return s.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 20);
    for (int _ = 0; _ < 50; _++) {
        vector<int> test(50);
        for (int i = 0; i < 50; i++) {
            test[i] = dis(gen);
        }
        ll ans = solve(test);
        ll ans_naive = solve_naive(test);
        assert(ans == ans_naive);
    }
    cout << "Test passed!" << endl;
#endif

    ll n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << solve(a) << '\n';

    return 0;
}