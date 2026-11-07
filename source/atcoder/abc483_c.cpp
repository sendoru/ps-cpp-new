// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> vote = a;
    vector<int> vote_cnt(n + 1);
    int winner = -1, max_vote = 0;
    vector<vector<int>> first_to_second(n + 1);
    for (int i = 0; i < m; i++) {
        vote_cnt[a[i]]++;
        first_to_second[a[i]].push_back(b[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (vote_cnt[i] > max_vote) {
            max_vote = vote_cnt[i];
            winner = i;
        }
    }
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        // treat special case individually
        if (i == winner) {
            continue;
        }
        int new_winner = winner, new_max_vote = max_vote;
        for (auto second : first_to_second[i]) {
            vote_cnt[second]++;
            if (vote_cnt[second] > new_max_vote || (vote_cnt[second] == new_max_vote && second < new_winner)) {
                new_max_vote = vote_cnt[second];
                new_winner = second;
            }
        }
        ans[i] = new_winner;
        for (auto second : first_to_second[i]) {
            vote_cnt[second]--;
        }
    }

    for (auto second : first_to_second[winner]) {
        vote_cnt[second]++;
    }
    vote_cnt[winner] = 0;
    int new_winner = -1;
    max_vote = 0;
    for (int i = 1; i <= n; i++) {
        if (vote_cnt[i] > max_vote) {
            max_vote = vote_cnt[i];
            new_winner = i;
        }
    }
    ans[winner] = new_winner;

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}