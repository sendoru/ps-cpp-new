#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX 100001

// �θ��� ������ ã���ִ� �迭
int parent[MAX];

using namespace std;

int findParent(int x, int* parent)
{
	if (parent[x] == x) return x;
	return parent[x] = findParent(parent[x], parent);
}

bool hasSameParents(int x, int y, int* parent)
{
	int xParent = findParent(x, parent);
	int yParent = findParent(y, parent);
	if (xParent == yParent) return true;
	else return false;
}

void unite(int x, int y, int* parent)
{
	int xParent = findParent(x, parent);
	int yParent = findParent(y, parent);
	if (xParent != yParent)
		parent[yParent] = xParent;
}

bool isXGreater(vector<int> a, vector<int> b)
{
	if (a[1] > b[1])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isYGreater(vector<int> a, vector<int> b)
{
	if (a[2] > b[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isZGreater(vector<int> a, vector<int> b)
{
	if (a[3] > b[3])
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(void)
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);


	// ������ ��Ƶ� ����. vector<pair<����ġ, pair<������, ������> > > ����
	vector < pair < int , pair<int, int> > > edges;

	for (int i = 0; i < MAX; i++)
	{
		parent[i] = i;
	}

	int countofPlanets;
	cin >> countofPlanets;
	// �༺ ��ȣ, x��ǥ, y��ǥ, z��ǥ
	vector<vector<int>> planets(countofPlanets, vector<int>(4, 0));
	for (int i = 0; i < countofPlanets; i++)
	{
		planets[i][0] = i;
		cin >> planets[i][1] >> planets[i][2] >> planets[i][3];
	}

	// x�� �������� ���� �� ���� ����
	sort(planets.begin(), planets.end(), isXGreater);
	for (int i = 0; i < countofPlanets - 1; i++)
	{
		int minimum = min(abs(planets[i][1] - planets[i + 1][1]), min(abs(planets[i][2] - planets[i + 1][2]), abs(planets[i][3] - planets[i + 1][3])));
		edges.push_back(make_pair(minimum, make_pair( planets[i][0], planets[i + 1][0] )));
	}
	// y�� �������� ���� �� ���� ����
	sort(planets.begin(), planets.end(), isYGreater);
	for (int i = 0; i < countofPlanets - 1; i++)
	{
		int minimum = min(abs(planets[i][1] - planets[i + 1][1]), min(abs(planets[i][2] - planets[i + 1][2]), abs(planets[i][3] - planets[i + 1][3])));
		edges.push_back(make_pair(minimum, make_pair(planets[i][0], planets[i + 1][0])));
	}
	// z�� �������� ���� �� ���� ����
	sort(planets.begin(), planets.end(), isZGreater);
	for (int i = 0; i < countofPlanets - 1; i++)
	{
		int minimum = min(abs(planets[i][1] - planets[i + 1][1]), min(abs(planets[i][2] - planets[i + 1][2]), abs(planets[i][3] - planets[i + 1][3])));
		edges.push_back(make_pair(minimum, make_pair(planets[i][0], planets[i + 1][0])));
	}

	sort(edges.begin(), edges.end());

	long long sum = 0;
	int count = 0;

	for (int i = 0; i < edges.size(); i++)
	{
		if (hasSameParents(edges[i].second.first, edges[i].second.second, parent) == false)
		{
			unite(edges[i].second.first, edges[i].second.second, parent);
			sum += edges[i].first;
			count++;
			if (count == countofPlanets - 1)
			{
				break;
			}
		}
	}

	cout << sum << endl;

	return 0;
}
