// #include "atcoder/all"
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
// using namespace atcoder;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const int BUCKET_SIZE = 12345;

vector<int> solve(vector<int> &idxs) {
    // assuming bucket size is 5e5 / 5e2 = 1e3
    vector<deque<int>> buckets((int)5e5 / BUCKET_SIZE + 1);
    for (int i = 0; i < idxs.size(); i++) {
        buckets[idxs[i] / BUCKET_SIZE].insert(buckets[idxs[i] / BUCKET_SIZE].begin() + idxs[i] % BUCKET_SIZE, i);
        for (int j = 0; j < buckets.size() - 1; j++) {
            if (buckets[j].size() > BUCKET_SIZE) {
                // move the last element to the next bucket
                buckets[j + 1].push_front(buckets[j].back());
                buckets[j].pop_back();
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < buckets.size(); i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            ans.push_back(buckets[i][j]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    random_device rnd;
    mt19937 mt(rnd());
    // randint
    uniform_int_distribution<int> dist((int)2e5, (int)5e5 - 1);

    vector<int> random_idxs((int)5e5);
    for (int i = 0; i < (int)5e5; i++) {
        random_idxs[i] = dist(mt) % (i + 1);
    }

    auto start = chrono::steady_clock::now();
    auto ans = solve(random_idxs);
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration<double, milli>(diff).count() << " ms" << endl;

#else

    int n;
    cin >> n;

    vector<int> idxs(n);
    for (int i = 0; i < n; i++) {
        cin >> idxs[i];
        idxs[i]--;
    }
    auto ans = solve(idxs);

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }
#endif

    return 0;
}