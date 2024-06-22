#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// #define DEBUG

bool solved = false;
vector<pii> ans;

pair<int, vector<int>> find_singularities(const vector<int> &v)
{
    int n = 0;
    vector<int> singularities;
    singularities.push_back(0);
    singularities.push_back(v.size() - 1);
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i] + 1 != v[i + 1] && v[i] - 1 != v[i + 1]) {
            singularities.push_back(i);
            singularities.push_back(i + 1);
            n++;
        }
    }
    sort(singularities.begin(), singularities.end());
    singularities.erase(unique(singularities.begin(), singularities.end()),
                        singularities.end());
    return {n, singularities};
}

void solve(vector<int> v, int remain_cnt, vector<pii> trace)
{
    if (solved) {
        return;
    }

    auto [n, sing] = find_singularities(v);

    if (n == 0 && v[0] == 0 && v.back() == v.size() - 1) {
        solved = true;
        ans = trace;
        return;
    }

    if (n > 2 * remain_cnt || n == 0) {
        return;
    }

    for (int i = 0; i < sing.size(); i++) {
        for (int j = i + 1; j < sing.size(); j++) {
            vector<int> tmp = v;
            reverse(tmp.begin() + sing[i], tmp.begin() + sing[j] + 1);
            vector<pii> new_trace = trace;
            new_trace.push_back({sing[i], sing[j]});
            solve(tmp, remain_cnt - 1, new_trace);
            if (solved) {
                return;
            }
        }
    }
}

bool test(int vec_size)
{
    vector<int> v(vec_size);
    for (int i = 0; i < vec_size; i++) {
        v[i] = i;
    }

    // integer random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, vec_size - 1);

    vector<pii> shuffle;
    for (int i = 0; i < 3; i++) {
        shuffle.push_back({dis(gen), dis(gen)});
        if (shuffle.back().first > shuffle.back().second) {
            swap(shuffle.back().first, shuffle.back().second);
        }
    }

    for (int i = 0; i < 3; i++) {
        reverse(v.begin() + shuffle[i].first,
                v.begin() + shuffle[i].second + 1);
    }

    solved = false;
    ans.clear();
    solve(v, 3, {});
    if (!solved) {
        cout << "Failed: couldn't find solution\n";
        return false;
    }

    if (ans.size() > 3) {
        cout << "Failed: too many operations\n";
        return false;
    }

    // recheck
    for (auto [a, b] : ans) {
        reverse(v.begin() + a, v.begin() + b + 1);
    }

    for (int i = 0; i < vec_size; i++) {
        if (v[i] != i) {
            cout << "Failed: wrong answer\n";
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
    bool passed = true;
    for (int i = 10; i < 200; i++) {
        for (int t = 0; t < 50; t++) {
            if (!test(i)) {
                cout << "Failed: n = " << i << '\n';
                passed = false;
                // return 0;
            }
        }
    }
    if (passed)
        cout << "Passed all tests\n";

    return 0;
#endif

#ifndef DEBUG
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;
    }

    solve(v, 3, {});
    if (solved) {
        while (ans.size() < 3) {
            ans.push_back({0, 0});
        }
        for (auto [a, b] : ans) {
            cout << a + 1 << ' ' << b + 1 << '\n';
        }
    }

    else {
        cout << -1;
    }

    return 0;
#endif
}

// 6 7 8 2 1 '9' 3 4 '5' 10
// 6 9 -> '6' 7 8 2 '1' 5 4 3 9 10
// 1 5 -> 1 2 '8' 7 6 5 4 '3' 9 10
// 3 8 -> 1 2 3 4 5 6 7 8 9 10