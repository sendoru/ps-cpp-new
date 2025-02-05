#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ld get_t(pll a, pll b) {
    ll dist = b.first - a.first;
    ll rel_speed = a.second - b.second;
    if (rel_speed == 0 || dist * rel_speed < 0) {
        return 1e18;
    }
    return (ld)dist / rel_speed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    set<ll> alive;
    for (int i = 0; i < n; i++) {
        alive.insert(i);
    }

    priority_queue<tuple<ld, ll, ll>, vector<tuple<ld, ll, ll>>, greater<>> pq;
    for (int i = 0; i < n - 1; i++) {
        pq.push({get_t(v[i], v[i + 1]), i, i + 1});
    }

    while (!pq.empty()) {
        auto [t, a, b] = pq.top();
        if (t == 1e18) {
            break;
        }
        pq.pop();
        if (alive.find(a) == alive.end() || alive.find(b) == alive.end()) {
            continue;
        }
        alive.erase(a);
        alive.erase(b);
        auto iter = alive.lower_bound(a);
        if (iter != alive.begin()) {
            ll prev_a = *prev(iter);
            iter = alive.lower_bound(b);
            if (iter != alive.end()) {
                ll next_b = *iter;
                pq.push({get_t(v[prev_a], v[next_b]), prev_a, next_b});
            }
        }
    }

    cout << alive.size() << endl;
    for (auto x : alive) {
        cout << x + 1 << " ";
    }

    return 0;
}