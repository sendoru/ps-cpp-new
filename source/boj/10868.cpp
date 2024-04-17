#include <iostream>
#include <cmath>
#include <vector>
#define INF 9998765643210

using namespace std;
typedef long long ll;

// a: ó�� �־����� ����
// tree: ���׸�Ʈ Ʈ��
// node: ���׸�Ʈ Ʈ���� ��� ��ȣ
// start, end: ���׸�Ʈ Ʈ���� ����ϴ� ���� ������ start ~ end
ll min(ll a, ll b)
{
	return a < b ? a : b;
}

ll max(ll a, ll b)
{
	return a > b ? a : b;
}

ll initMin(vector<ll>& a, vector<ll>& tree, int node, int start, int end)
{
	// node�� ���� ����� ���
	if (start == end)
	{
		return tree[node] = a[start];
	}
	else
	{
		return tree[node] = min(initMin(a, tree, node * 2, start, (start + end) / 2), initMin(a, tree, node * 2 + 1, (start + end) / 2 + 1, end));
	}
}

ll initMax(vector<ll>& a, vector<ll>& tree, int node, int start, int end)
{
	// node�� ���� ����� ���
	if (start == end)
	{
		return tree[node] = a[start];
	}
	else
	{
		return tree[node] = max(initMax(a, tree, node * 2, start, (start + end) / 2), initMax(a, tree, node * 2 + 1, (start + end) / 2 + 1, end));
	}
}

// left, right: �ּڰ��� ���ϴ� ������ left ~ right
// ������ ���������� init�� �Ȱ���
ll min(vector<ll>& tree, int node, int start, int end, int left, int right)
{
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start)
	{
		return INF;
	}
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end)
	{
		return tree[node];
	}
	return min(min(tree, node * 2, start, (start + end) / 2, left, right), min(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

ll max(vector<ll>& tree, int node, int start, int end, int left, int right)
{
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start)
	{
		return -INF;
	}
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end)
	{
		return tree[node];
	}
	return max(max(tree, node * 2, start, (start + end) / 2, left, right), max(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

int main(void)
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, M;
	cin >> N >> M;

	vector<ll> a(N);
	for (int i = 0; i < N; i++)
	{
		cin >> a[i];
	}
	
	int h = (int)ceil(log2(N));
	int treeSize = 1 << h + 1;
	vector<ll> minTree(treeSize, INF);
	vector<ll> maxTree(treeSize, -INF);
	initMin(a, minTree, 1, 0, N - 1);
	initMax(a, maxTree, 1, 0, N - 1);

	for (int i = 0; i < M; i++)
	{
		int left, right;
		cin >> left >> right;
		left--;
		right--;
		cout << min(minTree, 1, 0, N - 1, left, right) << ' ' << max(maxTree, 1, 0, N - 1, left, right) << '\n';
	}

	return 0;
}