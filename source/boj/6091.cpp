#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 100001

// �θ��� ������ ã���ִ� �迭

using namespace std;

int findParent(int x, vector<int>& parent)
{
	if (parent[x] == x) return x;
	return parent[x] = findParent(parent[x], parent);
}

bool hasSameParents(int x, int y, vector<int>& parent)
{
	int xParent = findParent(x, parent);
	int yParent = findParent(y, parent);
	if (xParent == yParent) return true;
	else return false;
}

void unite(int x, int y, vector<int>& parent)
{
	int xParent = findParent(x, parent);
	int yParent = findParent(y, parent);
	if (xParent != yParent)
		parent[yParent] = xParent;
}

int main(void)
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);


	// ������ ��Ƶ� ����. vector<pair<����ġ, pair<������, ������> > > ����
	vector<pair<int, pair<int, int>>> edges, mst;
	int n;
	cin >> n;
	vector<int> parent(n + 1);
	vector<vector<int>> adjList(n + 1);
	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int c;
			cin >> c;
			edges.push_back({ c, {i, j} });
		}
	}
	sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size(); i++)
	{
		int s = edges[i].second.second, e = edges[i].second.first, c = edges[i].first;
		if (!hasSameParents(s, e, parent))
		{
			unite(s, e, parent);
			mst.push_back(edges[i]);
		}
		if (mst.size() == n - 1)
		{
			break;
		}
	}

	for (auto edge : mst)
	{
		adjList[edge.second.first].push_back(edge.second.second);
		adjList[edge.second.second].push_back(edge.second.first);
	}
	for (int i = 1; i < adjList.size(); i++)
	{
		sort(adjList[i].begin(), adjList[i].end());
		cout << adjList[i].size() << ' ';
		for (auto adj : adjList[i])
		{
			cout << adj << ' ';
		}
		cout << '\n';
	}

	return 0;
}
