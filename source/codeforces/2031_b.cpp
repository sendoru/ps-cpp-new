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

bool solve(vector<int> &p) {
    bool ans = true;

    for (int i = 0; i < p.size(); i++) {
        if (abs(p[i] - i) > 1) {
            ans = false;
            break;
        }
    }

    return ans;
}

bool solve_old(vector<int> &p) {
    int n = p.size();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (p[j] > p[j + 1] && abs(p[i] - p[j + 1]) == 1) {
                swap(p[j], p[j + 1]);
            }
        }
    }
    return is_sorted(p.begin(), p.end());
}

vector<int> gen_right_case(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    auto rng = default_random_engine{};
    uniform_int_distribution<int> dist(0, n - 1);
    for (int i = 0; i < n; i++) {
        int j = dist(rng);
        if (abs(p[j] - p[j + 1]) == 1) {
            swap(p[j], p[j + 1]);
        }
    }

    return p;
}

vector<int> gen_wrong_case(int n) {
    auto p = gen_right_case(n);
    auto rng = default_random_engine{};
    uniform_int_distribution<int> dist(0, n - 1);
    bool swapped_wrong = false;
    while (!swapped_wrong) {
        for (int i = 0; i < n; i++) {
            int j = dist(rng);
            swap(p[j], p[j + 1]);
            if (abs(p[j] - p[j + 1]) != 1) {
                swapped_wrong = true;
                break;
            }
        }
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (int i = 0; i < 100; i++) {
        auto p = gen_right_case(50);
        bool ans = solve(p);
        if (!ans) {
            cout << "Failed (expected: true)" << endl;
            for (int i = 0; i < 50; i++) {
                cout << p[i] << " ";
            }
            cout << endl;
            break;
        }
    }
    for (int i = 0; i < 100; i++) {
        auto p = gen_wrong_case(50);
        bool ans = solve(p);
        if (ans) {
            cout << "Failed (expected: false)" << endl;
            for (int i = 0; i < 50; i++) {
                cout << p[i] << " ";
            }
            cout << endl;
            break;
        }
    }
#else
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
        }

        vector<int> sorted(n);
        for (int i = 0; i < n; i++) {
            sorted[i] = i;
        }

        bool ans = solve(p);

        cout << (ans ? "YES" : "NO") << endl;
    }
#endif

    return 0;
}