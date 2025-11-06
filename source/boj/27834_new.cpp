#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

// canonicalize label vector: map distinct positive labels to 1..k by first occurrence
vector<int> canonicalize(const vector<int> &a) {
    vector<int> res = a;
    unordered_map<int, int> mp;
    int next = 1;
    for (int x : res) {
        if (x == 0)
            continue;
        if (!mp.count(x))
            mp[x] = next++;
    }
    for (int &x : res)
        if (x != 0)
            x = mp[x];
    return res;
}

// encode vector<int> (length N, small labels) to integer key for unordered_map
uint64_t pack_key(const vector<int> &v) {
    // pack into 64-bit: 4 bits per entry (enough for N<=8 and labels <=15)
    uint64_t k = 0;
    for (int i = 0; i < (int)v.size(); ++i) {
        k |= (uint64_t)(v[i] & 0xF) << (4 * i);
    }
    return k;
}

struct UF {
    int n;
    vector<int> p;
    UF(int n = 0) : n(n), p(n) {
        for (int i = 0; i < n; ++i)
            p[i] = i;
    }
    int find(int a) { return p[a] == a ? a : p[a] = find(p[a]); }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b)
            p[b] = a;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M))
        return 0;
    // Ensure N <= M as statement says
    if (N > M)
        swap(N, M);

    // Precompute masks ranges
    int VmaskMax = 1 << (N - 1); // vertical connections inside a column
    int RmaskMax = 1 << N;       // right connections from each row to next column

    // DP maps: packed state -> big integer count
    unordered_map<uint64_t, cpp_int> dp, ndp;

    // initial state: all zeros (no open labels)
    vector<int> init(N, 0);
    dp[pack_key(init)] = 1;

    for (int col = 0; col < M; ++col) {
        ndp.clear();
        // for each previous state
        for (auto &pr : dp) {
            uint64_t key = pr.first;
            cpp_int ways = pr.second;

            // unpack key to prev_labels
            vector<int> prev_labels(N);
            uint64_t t = key;
            for (int i = 0; i < N; ++i) {
                prev_labels[i] = int(t & 0xF);
                t >>= 4;
            }

            // iterate over all possible vertical connections inside this column
            for (int vm = 0; vm < VmaskMax; ++vm) {
                UF uf(N);
                // union rows that come from same prev label (they belonged to same open component from left)
                for (int i = 0; i < N; ++i)
                    for (int j = i + 1; j < N; ++j)
                        if (prev_labels[i] != 0 && prev_labels[i] == prev_labels[j])
                            uf.unite(i, j);
                // apply vertical connections according to vm
                for (int i = 0; i + 1 < N; ++i)
                    if (vm & (1 << i))
                        uf.unite(i, i + 1);

                // For each choice of right-edges (which rows connect to next column)
                for (int rm = 0; rm < RmaskMax; ++rm) {
                    // determine which components (represented by UF roots) are open to right
                    unordered_map<int, int> compOpen; // root -> 0/1
                    for (int i = 0; i < N; ++i) {
                        if (rm & (1 << i))
                            compOpen[uf.find(i)] = 1;
                        else if (!compOpen.count(uf.find(i)))
                            compOpen[uf.find(i)] = 0;
                    }
                    // build next labels: for each row, if its component is open, give it a label id
                    vector<int> next(N, 0);
                    unordered_map<int, int> labelMap;
                    int nextId = 1;
                    for (int i = 0; i < N; ++i) {
                        int r = uf.find(i);
                        if (compOpen[r]) {
                            if (!labelMap.count(r))
                                labelMap[r] = nextId++;
                            next[i] = labelMap[r];
                        } else
                            next[i] = 0;
                    }
                    // canonicalize next
                    vector<int> can = canonicalize(next);
                    uint64_t nk = pack_key(can);
                    ndp[nk] += ways;
                }
            }
        }
        dp.swap(ndp);
    }

    // final answer is DP state with all zeros (all components closed)
    vector<int> finalZero(N, 0);
    uint64_t finalKey = pack_key(finalZero);
    cpp_int ans = dp.count(finalKey) ? dp[finalKey] : 0;

    // print big integer
    std::string out = ans.convert_to<string>();
    cout << out << "\n";
    return 0;
}
