#include "coloring.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_PAINT_CNT = 7200;

void ColoringSame(int N) {
    // cout << "N: " << N << endl;
    int pre_1 = -1;
    int l = 2, r = N;
    int colored_cnt = 0;
    while (l <= r) {
        // search in [l, m]
        int m = (l + r) / 2;
        for (int i = 2; i <= m; i++) {
            // cout << "Coloring " << i << endl;
            Color(i);
            colored_cnt++;
        }
        int cnt = GetColor(1);
        // 1 not painted, pre_1 is out of range
        if (cnt) {
            l = m + 1;
        }
        // 1 painted, pre_1 is in range
        else {
            pre_1 = m;
            r = m - 1;
        }
    }
    // cout << "pre_1: " << pre_1 << endl;
    vector<int> perm;
    for (int i = 1; i <= N; i++) {
        if (i != pre_1) {
            perm.push_back(i);
        }
    }
    auto rng = std::default_random_engine{};
    while (colored_cnt + perm.size() <= MAX_PAINT_CNT) {
        shuffle(perm.begin() + 1, perm.end(), rng);
        for (auto x : perm) {
            Color(x);
            colored_cnt++;
        }
    }
}
