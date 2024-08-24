#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct cmp {
    bool operator()(vector<int> &a, vector<int> &b) const
    {
        return a[2] > b[2];
    }
};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int idx, s, e;
        cin >> idx >> s >> e;
        a[i] = {idx, s, e};
    }

    sort(
        a.begin(),
        a.end(),
        [&](vector<int> &a, vector<int> &b) -> bool { return a[1] < b[1]; });

    priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
    vector<int> available;
    vector<int> ans(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        while (!pq.empty() && pq.top()[2] <= a[i][1]) {
            available.push_back(pq.top()[3]);
            pq.pop();
        }
        auto tmp = a[i];
        if (available.empty()) {
            tmp.push_back(pq.size() + 1);
        }
        else {
            tmp.push_back(available.back());
            available.pop_back();
        }
        pq.push(tmp);
        ans[tmp[0] - 1] = tmp[3];
        cnt = max(cnt, (int)(pq.size()));
    }

    cout << cnt << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

/*
3 8
7 13
2 14
12 18
6 20
15 21
20 25
6 27
*/