// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int solve(vector<bitset<10>> s_bit, int cur_row) {
    if (cur_row == 10) {
        return 0;
    }

    int ans = 9999;
    if (cur_row == 0) {
        // cur_row에서 0 ~ 1023 전부 시도
        for (int i = 0; i < (1 << 10); i++) {
            auto s_bit_next = s_bit;
            for (int j = 0; j < 10; j++) {
                if ((i >> j) & 1) {
                    // s_bit_next[cur_row][j] 자기 자신 및 상하좌우 뒤집기
                    s_bit_next[cur_row][j] = !s_bit_next[cur_row][j];
                    if (cur_row > 0) {
                        s_bit_next[cur_row - 1][j] = !s_bit_next[cur_row - 1][j]; // 위
                    }
                    if (cur_row < 9) {
                        s_bit_next[cur_row + 1][j] = !s_bit_next[cur_row + 1][j]; // 아래
                    }
                    if (j > 0) {
                        s_bit_next[cur_row][j - 1] = !s_bit_next[cur_row][j - 1]; // 왼쪽
                    }
                    if (j < 9) {
                        s_bit_next[cur_row][j + 1] = !s_bit_next[cur_row][j + 1]; // 오른쪽
                    }
                }
            }

            // 다음 줄로 넘어가기
            int next_ans = solve(s_bit_next, cur_row + 1);
            ans = min(ans, next_ans + __builtin_popcount(i));
        }
    }

    else {
        // 이전 줄이 0이 되게 하는 경우만 따지자
        auto s_bit_next = s_bit;
        int prev_popcount = s_bit[cur_row - 1].count();
        for (int j = 0; j < 10; j++) {
            if (s_bit[cur_row - 1][j]) {
                // s_bit_next[cur_row][j] 자기 자신 및 상하좌우 뒤집기
                s_bit_next[cur_row][j] = !s_bit_next[cur_row][j];
                if (cur_row > 0) {
                    s_bit_next[cur_row - 1][j] = !s_bit_next[cur_row - 1][j]; // 위
                }
                if (cur_row < 9) {
                    s_bit_next[cur_row + 1][j] = !s_bit_next[cur_row + 1][j]; // 아래
                }
                if (j > 0) {
                    s_bit_next[cur_row][j - 1] = !s_bit_next[cur_row][j - 1]; // 왼쪽
                }
                if (j < 9) {
                    s_bit_next[cur_row][j + 1] = !s_bit_next[cur_row][j + 1]; // 오른쪽
                }
            }
        }

        // 현재 줄이 마지막 줄이고 1이 남은 경우는 불가능
        if (cur_row == 9 && s_bit_next[cur_row].count() != 0) {
            return ans; // 불가능한 경우
        }

        // 다음 줄로 넘어가기
        int next_ans = solve(s_bit_next, cur_row + 1);
        ans = next_ans + prev_popcount;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<string> s(10);
    for (int i = 0; i < 10; ++i) {
        cin >> s[i];
    }

    vector<bitset<10>> s_bit(10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (s[i][j] == 'O') {
                s_bit[i] |= (1 << j);
            }
        }
    }

    int ans = solve(s_bit, 0);
    if (ans >= 9999) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}