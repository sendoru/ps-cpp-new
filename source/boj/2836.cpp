#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<pii> v;
    for (int i = 0; i < n; i++) {
        ll s, e;
        cin >> s >> e;
        if (e < s) {
            v.emplace_back(s, 1);
            v.emplace_back(e, -1);
        }
    }

    ll ans = m;
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        v[i].second *= -1;
    }
    int cnt = 0;
    int cur = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second == 1) {
            cnt++;
            if (cur == -1) {
                cur = v[i].first;
            }
        }
        else {
            cnt--;
            if (cnt == 0) {
                ans += 2 * (v[i].first - cur);
                cur = -1;
            }
        }
    }

    cout << ans;
    return 0;
}