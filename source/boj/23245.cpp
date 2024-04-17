#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
typedef long long ll;
constexpr ll MAX = 1000000;

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


int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	vector<pair<ll, ll>> ab(n);
	for (int i = 0; i < n; i++) cin >> ab[i].first;
	for (int i = 0; i < n; i++) cin >> ab[i].second;
	sort(ab.begin(), ab.end());

	vector<ll> segTree(2 * MAX + 5);
	ll ans = 0;
	ll idx = 0;
	for (int i = 0; i <= MAX; i++)
	{
		ll initIdx = idx;

		// �ձ��ϱ�
		while (idx < ab.size() && i >= ab[idx].first)
		{
			ll cnt = sum(segTree, 1, 0, MAX, 0, ab[idx].second - 1);
			ans += cnt * (cnt - 1) / 2;
			idx++;
		}

		// ������Ʈ
		idx = initIdx;
		while (idx < ab.size() && i >= ab[idx].first)
		{
			ll cnt = sum(segTree, 1, 0, MAX, ab[idx].second, ab[idx].second);
			if (cnt == 0)
				update(segTree, 1, 0, MAX, ab[idx].second, 1);
			idx++;
		}
	}

	cout << ans;
	return 0;
}