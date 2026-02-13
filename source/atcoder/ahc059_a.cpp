// #include "atcoder/all"
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Pos {
    int r, c;
};

int N;
int grid[20][20];
vector<Pos> card_pos[200]; // 숫자별 위치 (최대 N*N/2 = 200)

inline int get_dist(Pos a, Pos b) {
    return abs(a.r - b.r) + abs(a.c - b.c);
}

// 현재 경로의 총 이동 거리 계산
int calculate_dist(const vector<pair<int, int>> &path) {
    Pos curr = {0, 0};
    int total = 0;
    for (auto &p : path) {
        total += get_dist(curr, card_pos[p.first][p.second]);
        curr = card_pos[p.first][p.second];
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;
    int num_pairs = (N * N) / 2;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            card_pos[grid[i][j]].push_back({i, j});
        }
    }

    // 초기 해 생성 (단순 순서)
    vector<pair<int, int>> P;
    vector<int> initial_vals(num_pairs);
    iota(initial_vals.begin(), initial_vals.end(), 0);

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(initial_vals.begin(), initial_vals.end(), rng);

    for (int v : initial_vals) {
        P.push_back({v, 0});
        P.push_back({v, 1});
    }

    int current_dist = calculate_dist(P);
    vector<pair<int, int>> best_P = P;
    int best_dist = current_dist;

    auto start_time = chrono::steady_clock::now();
    double T = 200.0;
    double factor = 0.99995;

    // Simulated Annealing 루프
    while (true) {
        auto now = chrono::steady_clock::now();
        if (chrono::duration<double>(now - start_time).count() > 1.85)
            break;

        // 1. 임의의 구간 제거 (길이 10~20)
        int len = uniform_int_distribution<int>(10, 20)(rng);
        if (len >= P.size())
            continue;
        int start_idx = uniform_int_distribution<int>(0, P.size() - len)(rng);

        vector<pair<int, int>> P_prime;
        vector<int> to_reinsert;
        vector<int> counts(num_pairs, 0);

        for (int i = 0; i < P.size(); ++i) {
            if (i >= start_idx && i < start_idx + len)
                continue;
            P_prime.push_back(P[i]);
            counts[P[i].first]++;
        }

        // 짝이 안 맞는 숫자 추출
        vector<pair<int, int>> final_P_prime;
        vector<bool> needs_reinsert(num_pairs, false);
        for (auto &p : P_prime) {
            if (counts[p.first] == 2)
                final_P_prime.push_back(p);
            else
                needs_reinsert[p.first] = true;
        }
        for (int i = 0; i < P.size(); ++i) {
            if (i >= start_idx && i < start_idx + len)
                needs_reinsert[P[i].first] = true;
        }

        for (int i = 0; i < num_pairs; ++i)
            if (needs_reinsert[i])
                to_reinsert.push_back(i);
        shuffle(to_reinsert.begin(), to_reinsert.end(), rng);

        // 2. 그리디하게 다시 삽입
        vector<pair<int, int>> next_P = final_P_prime;
        int next_dist = 0; // 나중에 한 번에 계산하거나 증분 계산

        for (int v : to_reinsert) {
            int best_pos = 0;
            int min_inc = 2e9;
            int best_order = 0;

            for (int i = 0; i <= next_P.size(); ++i) {
                Pos p_prev = (i == 0) ? Pos{0, 0} : card_pos[next_P[i - 1].first][next_P[i - 1].second];
                Pos p_next = (i == next_P.size()) ? card_pos[next_P.back().first][next_P.back().second] : card_pos[next_P[i].first][next_P[i].second];

                for (int order = 0; order < 2; ++order) {
                    Pos c1 = card_pos[v][order];
                    Pos c2 = card_pos[v][1 - order];

                    int inc = get_dist(p_prev, c1) + get_dist(c1, c2);
                    if (i < next_P.size())
                        inc += get_dist(c2, p_next) - get_dist(p_prev, p_next);

                    if (inc < min_inc) {
                        min_inc = inc;
                        best_pos = i;
                        best_order = order;
                    }
                }
            }
            next_P.insert(next_P.begin() + best_pos, {v, 1 - best_order});
            next_P.insert(next_P.begin() + best_pos, {v, best_order});
        }

        next_dist = calculate_dist(next_P);

        // 3. SA 결정
        if (next_dist <= current_dist || exp((current_dist - next_dist) / T) > uniform_real_distribution<double>(0, 1)(rng)) {
            P = next_P;
            current_dist = next_dist;
            if (current_dist < best_dist) {
                best_dist = current_dist;
                best_P = P;
            }
        }
        T *= factor;
    }

    // 최종 경로 출력
    string ans = "";
    Pos curr = {0, 0};
    for (auto &p : best_P) {
        Pos target = card_pos[p.first][p.second];
        while (curr.r < target.r) {
            ans += "D\n";
            curr.r++;
        }
        while (curr.r > target.r) {
            ans += "U\n";
            curr.r--;
        }
        while (curr.c < target.c) {
            ans += "R\n";
            curr.c++;
        }
        while (curr.c > target.c) {
            ans += "L\n";
            curr.c--;
        }
        ans += "Z\n";
    }
    cout << ans << endl;

    return 0;
}