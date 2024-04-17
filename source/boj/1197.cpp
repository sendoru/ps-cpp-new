#include <iostream>
#include <vector>
#include <queue>
typedef long long ll;
using namespace std;

// �̰� ���� ����Ʈ
// graph[i]�� {j, c}�� ���Ե� : i���� j�� ���� ��� c�� ������ ����
pair<ll,vector<vector<int>>> findMST(vector<vector<pair<int, int>>>& graph) {
    vector<bool> included(graph.size());

    ll mstCost = 0;
    vector<vector<int>> mst;
    // pq���� �� ������ {���� ���, ������, ������} ���·�
    // ���� ����� ���� ���� top�� ������ �����
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({ 0, 1, 1 });

    while (!pq.empty())
    {
        auto curEdge = pq.top();
        pq.pop();
        if (!included[curEdge[2]])
        {
            included[curEdge[2]] = true;
            mstCost += curEdge[0];
            if (curEdge[1] != curEdge[2]) mst.push_back(curEdge);
            for (auto nextNode : graph[curEdge[2]])
            {
                if (!included[nextNode.first])
                {
                    pq.push({ nextNode.second, curEdge[2], nextNode.first });
                }
            }
        }
    }

    return make_pair(mstCost, mst);
}


int main(void)
{
    int v, e;
    cin >> v >> e;
    vector<vector<pair<int, int>>> graph(v + 1);
    for (int i = 0; i < e; i++)
    {
        int s, e, c;
        cin >> s >> e >> c;
        graph[s].push_back({ e, c });
        graph[e].push_back({ s, c });
    }
    auto ans = findMST(graph);
    cout << ans.first;
    return 0;
}