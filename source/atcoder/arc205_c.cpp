#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Person {
    int id, start, end;
};

int op(int a, int b) { return max(a, b); }
int e() { return 0; }

vector<int> solve(vector<Person> &people) {
    vector<Person> to_right, to_left;
    vector<int> imos(2 * people.size() + 10, 0);
    for (const auto &p : people) {
        if (p.start < p.end) {
            to_right.push_back(p);
        } else {
            to_left.push_back(p);
        }
    }

    bool possible = true;
    vector<Person> right_ordered, left_ordered;

    // right
    sort(to_right.begin(), to_right.end(), [](const Person &a, const Person &b) {
        return a.end > b.end;
    });

    for (auto &elem : to_right) {
        if (right_ordered.empty() || right_ordered.back().start > elem.start) {
            right_ordered.push_back(elem);
            imos[elem.start]++;
            imos[elem.end + 1]--;
        } else {
            possible = false;
            return {};
        }
    }

    if (to_left.empty()) {
        vector<int> ans;
        for (const auto &p : right_ordered) {
            ans.push_back(p.id);
        }
        return ans;
    }

    // left
    for (int i = 1; i < (int)imos.size(); i++) {
        imos[i] += imos[i - 1];
    }

    sort(to_left.begin(), to_left.end(), [](const Person &a, const Person &b) {
        return a.end < b.end;
    });

    atcoder::segtree<int, op, e> seg(imos);

    for (auto &elem : to_left) {
        if (left_ordered.empty() || left_ordered.back().start < elem.start) {
            left_ordered.push_back(elem);
            ll cur_pf_sum = seg.prod(elem.end, elem.start + 1);
            if (cur_pf_sum != 0) {
                possible = false;
                return {};
            }
        } else {
            possible = false;
            return {};
        }
    }

    vector<int> ans;
    for (const auto &p : right_ordered) {
        ans.push_back(p.id);
    }
    for (const auto &p : left_ordered) {
        ans.push_back(p.id);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<Person> people(n);
    vector<int> coords;
    for (int i = 0; i < n; i++) {
        int s, e;
        cin >> s >> e;
        people[i] = {i + 1, s, e};
        coords.push_back(s);
        coords.push_back(e);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    for (auto &p : people) {
        p.start = lower_bound(coords.begin(), coords.end(), p.start) - coords.begin();
        p.end = lower_bound(coords.begin(), coords.end(), p.end) - coords.begin();
    }

    vector<int> ans = solve(people);
    if (ans.empty()) {
        cout << "No";
        return 0;
    }
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}