#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

struct Median {
    vector<int> count;
    int left_cnt, right_cnt;
    int left_sum, right_sum;
    // left 구간 = [0, ptr - 1], right 구간 = [ptr + 1, end]
    int cnt, ptr;

    Median() : count(200001), left_cnt(0), right_cnt(0), left_sum(0), right_sum(0), cnt(0), ptr(0) {}

    Median(int n) : count(n + 1), left_cnt(0), right_cnt(0), left_sum(0), right_sum(0), cnt(0), ptr(0) {}

    void insert(int x) {
        count[x]++;
        cnt++;

        if (cnt == 1) {
            left_cnt = right_cnt = 0;
            left_sum = right_sum = 0;
            ptr = x;
            return;
        }

        if (x < ptr) {
            left_cnt++;
            left_sum += x;
        } else if (x > ptr) {
            right_cnt++;
            right_sum += x;
        }

        if (left_cnt > cnt / 2) {
            while (left_cnt > cnt / 2) {
                left_cnt -= count[ptr - 1];
                left_sum -= (ptr - 1) * count[ptr - 1];
                right_cnt += count[ptr];
                right_sum += ptr * count[ptr];
                ptr--;
            }
        }
        if (right_cnt > cnt / 2) {
            while (right_cnt > cnt / 2) {
                right_cnt -= count[ptr + 1];
                right_sum -= (ptr + 1) * count[ptr + 1];
                left_cnt += count[ptr];
                left_sum += ptr * count[ptr];
                ptr++;
            }
        }
    }

    int getMedian() {
        return ptr;
    }

    int getL1Error() {
        int median = getMedian();
        return (median * left_cnt - left_sum) +
               (right_sum - median * right_cnt);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<pii> dots(n);
    for (int i = 0; i < n; i++) {
        cin >> dots[i].first >> dots[i].second;
    }

    sort(dots.begin(), dots.end());

    // dp[i][j] = 구간이 i개이고 마지막 점이 j일 떄 l1 error의 최솟값
    vector<vector<int>> dp(k + 1, vector<int>(n, 1e7));
    // 초기조건 i = 1
    Median _median(1010);
    for (int j = 0; j < n; j++) {
        _median.insert(dots[j].second);
        dp[1][j] = _median.getL1Error();
    }

    int ans = dp[1].back();

    for (int i = 2; i <= k; i++) {
        for (int j = i - 1; j < n; j++) {
            Median median(1010);
            for (int l = j - 1; l >= 0; l--) {
                median.insert(dots[l + 1].second);
                dp[i][j] = min(dp[i][j], dp[i - 1][l] + median.getL1Error());
            }
        }
        ans = min(ans, dp[i].back());
    }

    cout << ans << '\n';
    return 0;
}