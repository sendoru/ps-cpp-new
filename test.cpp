#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[123123];
vector<int> radj[123123];
bool visited[123123];
bool visited_r[123123];
int clk = 0;
int post[123123];
int pre[123123];
int v, e;
int ccflag;
int cc[123123];
vector<int> postorder;
vector<vector<int>> sccs;

// previsit 기록 함수
void previsit(int u) {
    pre[u] = clk++;
}

// postvisit 기록 함수
void postvisit(int u) {
    postorder.push_back(u);
    post[u] = clk++;
}

// 역 dfs
void rdfs(int cur) {
    visited_r[cur] = true;
    previsit(cur);
    for (int next : radj[cur]) {
        if (!visited_r[next])
            rdfs(next);
    }
    postvisit(cur);
}

// 정방향 dfs 및 해당 scc 컴포넌트 cc에 저장
void dfs(int cur) {
    sccs.back().push_back(cur);
    visited[cur] = 1;
    cc[cur] = ccflag;
    for (int next : adj[cur]) {
        if (!visited[next])
            dfs(next);
    }
}

int main(void) {
    cin >> v >> e;
    // edge 받기
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);  // adj 생성
        radj[b].push_back(a); // reverse adj 생성
    }

    // 정렬 추가필요

    // 역dfs 시작
    for (int i = 1; i <= v; i++) {
        if (!visited_r[i])
            rdfs(i);
    }

    for (int i = 1; i <= v; i++) {
        visited[i] = false;
    }

    // SCC 구하기
    ccflag = 1;
    for (int k = 1; k <= v; k++) {
        if (!visited[postorder[v - k]]) {
            sccs.push_back(vector<int>());
            dfs(postorder[v - k]);
            ccflag++;
        }
    }

    cout << sccs.size() << "\n";
    for (auto &scc : sccs) {
        sort(scc.begin(), scc.end());
    }
    sort(sccs.begin(), sccs.end());
    for (auto &scc : sccs) {
        for (int node : scc) {
            cout << node << " ";
        }
        cout << "-1\n";
    }

    return 0;
}