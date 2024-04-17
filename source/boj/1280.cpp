#include <iostream>
#include <cmath>
#include <vector>
#define MAX 200001ll
#define MOD 1'000'000'007ll

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

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	vector<ll> loc(n);
	for (int i = 0; i < n; i++) cin >> loc[i];
	ll treeSize = 1ll << (ll)ceil(log2((MAX + 1) << 1));
	vector<ll> cnt(treeSize), dist(treeSize);
	update(cnt, 1, 0, MAX + 1, loc[0], 1);
	update(dist, 1, 0, MAX + 1, loc[0], loc[0]);

	ll ans = 1;
	for (int i = 1; i < n; i++)
	{
		ll curCost = 0;
		curCost += sum(cnt, 1, 0, MAX + 1, 0, loc[i] - 1) * loc[i] - sum(dist, 1, 0, MAX + 1, 0, loc[i] - 1);
		curCost += sum(dist, 1, 0, MAX + 1, loc[i] + 1, MAX + 1) - sum(cnt, 1, 0, MAX + 1, loc[i] + 1, MAX + 1) * loc[i];
		update(cnt, 1, 0, MAX + 1, loc[i], 1);
		update(dist, 1, 0, MAX + 1, loc[i], loc[i]);
		ans *= curCost % MOD;
		ans %= MOD;
	}

	cout << ans;
	return 0;
}