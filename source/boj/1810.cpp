// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<double> dijk(vector<vector<pair<int, double>>> &adj_list, int start) {
    int n = adj_list.size();
    vector<double> dist(n, 1e12);
    dist[start] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [cur_d, cur_n] = pq.top();
        pq.pop();
        if (cur_d > dist[cur_n]) {
            continue;
        }
        for (auto [next_n, next_d] : adj_list[cur_n]) {
            if (dist[next_n] > cur_d + next_d) {
                dist[next_n] = cur_d + next_d;
                pq.push({dist[next_n], next_n});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, f;
    cin >> n >> f;
    n++;
    vector<pii> dots(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> dots[i].first >> dots[i].second;
    }
    set<pair<pii, int>> dots_set;
    for (int i = 0; i < n; i++) {
        dots_set.insert({dots[i], i});
    }
    vector<vector<pair<int, double>>> adj_list(n);
    for (int i = 0; i < n; i++) {
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                auto next = make_pair(dots[i].first + dx, dots[i].second + dy);
                auto iter = dots_set.lower_bound({next, -1});
                if (iter != dots_set.end() && iter->first == next) {
                    adj_list[i].push_back({iter->second, sqrt((double)dx * dx + dy * dy)});
                }
            }
        }
    }
    vector<double> dist = dijk(adj_list, n - 1);
    double ans = 1e12;
    for (int i = 0; i < n; i++) {
        if (dots[i].second == f && dist[i] < ans) {
            ans = dist[i];
        }
    }

    if (ans == 1e12) {
        cout << -1;
    } else {
        cout << (ll)round(ans);
    }

    return 0;
}