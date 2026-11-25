#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> order_to_type(k);
    for (int i = 0; i < k; i++) {
        cin >> order_to_type[i];
        order_to_type[i]--;
    }
    vector<vector<int>> type_to_order(k);
    for (int i = 0; i < k; i++) {
        type_to_order[order_to_type[i]].push_back(i);
    }
    for (int i = 0; i < k; i++) {
        type_to_order[i].push_back(1e9);
    }
    vector<vector<int>::iterator> iters(k);
    for (int i = 0; i < k; i++) {
        iters[i] = type_to_order[i].begin();
    }
    int ans = 0;
    vector<int> plug_to_type(n, -1);
    vector<int> empty_plugs(n);
    vector<int> type_to_plug(k, -1);
    iota(empty_plugs.begin(), empty_plugs.end(), 0);
    priority_queue<pii> pq;
    for (int i = 0; i < k; i++) {
        int cur_type = order_to_type[i];

        // 지금 순서인 게 이미 플러그에 꽃아져 있으면 그냥 놔두면 됨
        if (type_to_plug[cur_type] != -1) {
            iters[cur_type]++;
            pq.push({*iters[cur_type], cur_type});
            continue;
        }

        int nxt_plug;
        // 비어있는 플러그가 있으면 거기다 꽃기
        if (!empty_plugs.empty()) {
            nxt_plug = empty_plugs.back();
            empty_plugs.pop_back();
        }

        // optimal scheduling (다음 등장이 제일 늦은 type을 뽑고 거기다가 꽃음)
        else {
            int pre_time = pq.top().first;
            int pre_type = pq.top().second;
            pq.pop();
            int nxt_plug = type_to_plug[pre_type];
            type_to_plug[pre_type] = -1;
            ans++;
        }
        type_to_plug[cur_type] = nxt_plug;
        iters[cur_type]++;
        pq.push({*iters[cur_type], cur_type});
    }
    cout << ans;
}