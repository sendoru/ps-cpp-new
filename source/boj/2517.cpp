#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

// a: ó�� �־����� ����
// tree: ���׸�Ʈ Ʈ��
// node: ���׸�Ʈ Ʈ���� ��� ��ȣ
// start, end: ���׸�Ʈ Ʈ���� ����ϴ� ���� ������ start ~ end
ll init(vector<ll>& a, vector<ll>& tree, int node, int start, int end)
{
	// node�� ���� ����� ���
	if (start == end)
	{
		return tree[node] = a[start];
	}
	else
	{
		return tree[node] = init(a, tree, node * 2, start, (start + end) / 2) + init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
	}
}

// left, right: ���� ���ϴ� ������ left ~ right
// ������ ���������� init�� �Ȱ���
ll sum(vector<ll>& tree, int node, int start, int end, int left, int right)
{
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start)
	{
		return 0;
	}
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end)
	{
		return tree[node];
	}
	return sum(tree, node * 2, start, (start + end) / 2, left, right) + sum(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}

// diff: (������Ʈ�Ϸ��� ��) - (���� ��)
void update(vector<ll>& tree, int node, int start, int end, int index, ll diff)
{
	if (index < start || index > end) return;

	tree[node] += diff;

	if (start != end)
	{
		update(tree, node * 2, start, (start + end) / 2, index, diff);
		update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	// int t;
	// cin >> t;
	// while (t--)
	{
		int n;
		cin >> n;
		vector<pair<ll, ll>> skill(n);

		for (int i = 0; i < n; i++)
		{
			cin >> skill[i].first;
			skill[i].second = i;
		}
		sort(skill.begin(), skill.end());
		for (int i = 0; i < n; i++)
		{
			skill[i].first = i;
		}
		sort(skill.begin(), skill.end(), [](pair<ll, ll> a, pair<ll, ll> b) -> bool {return a.second < b.second; });

		int h = (int)ceil(log2(skill.size() + 1));
		int treeSize = 1 << (h + 1);
		vector<ll> tree(treeSize);
		vector<ll> treeBase(skill.size() + 1);
		init(treeBase, tree, 1, 0, skill.size());

		for (int i = 0; i < n; i++)
		{
			cout << sum(tree, 1, 0, n, skill[i].first + 1, n) + 1 << '\n';
			update(tree, 1, 0, n, skill[i].first, 1);
		}
	}

	return 0;
}