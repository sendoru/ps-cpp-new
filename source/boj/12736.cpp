// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int v = n + m;

    vector<int> parent(v + 1), cost(v + 1);

    for (int i = 2; i <= v; i++) {
        int p, c;
        cin >> p >> c;
        parent[i] = p;
        cost[i] = c;
    }

    vector<priority_queue<ll> *> pq(v + 1);
    for (int i = 1; i <= v; i++) {
        pq[i] = new priority_queue<ll>();
    }
    vector<ll> a(v + 1), b(v + 1);

    for (int i = v; i >= 2; i--) {
        ll p = 0, q = 0;
        if (a[i]) {
            for (int j = 1; j < a[i]; j++) {
                b[i] += pq[i]->top();
                pq[i]->pop();
            }
            p = pq[i]->top();
            pq[i]->pop();
            q = pq[i]->top();
            pq[i]->pop();
        }

        pq[i]->push(cost[i] + p);
        pq[i]->push(cost[i] + q);

        b[i] -= cost[i];

        auto &pt_cur = pq[i], &pt_par = pq[parent[i]];
        if (pt_cur->size() > pt_par->size()) {
            swap(pt_cur, pt_par);
        }

        while (!pt_cur->empty()) {
            pt_par->push(pt_cur->top());
            pt_cur->pop();
        }

        delete pq[i];

        a[parent[i]]++;
        b[parent[i]] += b[i];
    }

    ll ans = b[1];
    for (int i = 0; i < a[1]; i++) {
        ans += pq[1]->top();
        pq[1]->pop();
    }

    cout << ans << '\n';

    return 0;
}