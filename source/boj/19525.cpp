// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const int N = 150;

pair<int, vector<int>> get_score(vector<int> &cands) {
    vector<bool> diags(2 * (cands.size() - 1), false);
    for (int i : cands) {
        if (diags[i]) {
            continue;
        }
        bool possible = true;

        for (int d1 = 0; d1 <= 2 * (N - 1); d1++) {
            if (!diags[d1]) {
                continue;
            }
            for (int d2 = 0; d2 <= 2 * (N - 1); d2++) {
                if (!diags[d2]) {
                    continue;
                }
                int d3 = i + (d1 - i) + (d2 - i);
                if (!(d3 < 0 || d3 >= 2 * (N - 1) || !diags[d3])) {
                    possible = false;
                    break;
                }
                d3 = i + d2 - d1;
                if (!(d3 < 0 || d3 >= 2 * (N - 1) || !diags[d3])) {
                    possible = false;
                    break;
                }
            }
        }

        if (possible) {
            diags[i] = true;
        }
    }

    int cnt = 0;
    for (int i = 0; i < 2 * (N - 1); i++) {
        if (diags[i]) {
            cnt += N - abs(N - 1 - i);
        }
    }
    vector<int> diag_collected;
    for (int i = 0; i < 2 * (N - 1); i++) {
        if (diags[i]) {
            diag_collected.push_back(i);
        }
    }
    return {cnt, diag_collected};
}

vector<vector<int>> paint(const vector<int> &diags) {
    vector<vector<int>> ans(N, vector<int>(N, 0));
    for (int d : diags) {
        for (int r = 0; r < N; r++) {
            int c = d - r;
            if (c < 0 || c >= N) {
                continue;
            }
            ans[r][c] = 1;
        }
    }
    return ans;
}

bool check(const vector<int> &diags) {
    auto ans = paint(diags);
    for (int r1 = 0; r1 < N; r1++) {
        for (int r2 = r1 + 1; r2 < N; r2++) {
            for (int c1 = 0; c1 < N; c1++) {
                for (int c2 = c1 + 1; c2 < N; c2++) {
                    if (ans[r1][c1] && ans[r1][c2] && ans[r2][c1] && ans[r2][c2]) {
                        cerr << "Error: (" << r1 << "," << c1 << "), (" << r1 << "," << c2 << "), ("
                             << r2 << "," << c1 << "), (" << r2 << "," << c2 << ")\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int solve() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    random_device rd;
    mt19937 g(rd());
    geometric_distribution<int> dist_len(0.05);
    geometric_distribution<int> dist_pos(0.25);
    uniform_real_distribution<double> dist_prob(0.0, 1.0);

    vector<int> cur_cands = {N - 1, N - 2, N - 4, N - 8, N - 16, N - 32};
    for (int i = 0; i < 2 * (N - 1); i++) {
        if (find(cur_cands.begin(), cur_cands.end(), i) == cur_cands.end()) {
            cur_cands.push_back(i);
        }
    }
    shuffle(cur_cands.begin(), cur_cands.end(), g);

    int cur_score = 0, max_score = 0;
    vector<int> best_diags, cur_diags;
    double temperature = 1000.0;
    double cooling_rate = 0.9995;
    for (int iter = 0; iter < 10000; iter++) {
        if (max_score >= 1750) {
            break;
        }
        // random int generator to choose shuffle len
        int len = dist_len(g) + 2;
        int pos = dist_pos(g);
        auto new_cands = cur_cands;
        shuffle(new_cands.begin() + pos, new_cands.begin() + min(2 * (N - 1), pos + len), g);

        auto [score, diags] = get_score(new_cands);
        if (score >= cur_score) {
            cur_score = score;
            cur_diags = diags;
            cur_cands = new_cands;
        } else {
            double prob = exp((score - cur_score) / temperature);
            if (dist_prob(g) < prob) {
                cur_score = score;
                cur_diags = diags;
                cur_cands = new_cands;
            }
        }
        temperature *= cooling_rate;
        if (cur_score > max_score) {
            max_score = cur_score;
            best_diags = cur_diags;
        }
    }

    bool valid = check(best_diags);
    if (!valid) {
        cerr << "Invalid solution found!\n";
    }

    cout << max_score << "\n";
    cout << best_diags.size() << "\n";
    for (int d : best_diags) {
        cout << d << " ";
    }
    cout << "\n";

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
}