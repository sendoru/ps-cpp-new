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

pair<ll, ll> min(pair<ll, ll> a, pair<ll, ll> b)
{
	if (a.first > b.first)
	{
		return a;
	}
	if (a.first < b.first)
	{
		return b;
	}
	if (a.second > b.second)
	{
		return a;
	}
	return b;
}

pair<ll, ll> init(vector<pair<ll, ll> >& a, vector<pair<ll, ll> >& tree, int node, int start, int end)
{
	// node�� ���� ����� ���
	if (start == end)
	{
		return tree[node] = a[start];
	}
	else
	{
		return tree[node] = max(init(a, tree, node * 2, start, (start + end) / 2), init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end));
	}
}

// left, right: �ּڰ��� ���ϴ� ������ left ~ right
// ������ ���ڴ� init�� �Ȱ���
pair<ll, ll> getMax(vector<pair<ll, ll> >& tree, int node, int start, int end, int left, int right)
{
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start)
	{
		return { -INF, -1 };
	}
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end)
	{
		return tree[node];
	}
	return max(getMax(tree, node * 2, start, (start + end) / 2, left, right), getMax(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

void update(vector<pair<ll, ll> >& tree, int index, pair<ll, ll> newValue)
{
	int node = tree.size() / 2 + index;
	tree[node] = newValue;
	node /= 2;
	while (node != 0)
	{
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
		node /= 2;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);


	int n, m;
	cin >> n;
	int h = (int)ceil(log2(n + 1));
	int treeSize = 1 << (h + 1);
	vector<pair<ll, ll> > a(n + 1);
	vector<pair<ll, ll> > tree(treeSize);
	a[0] = { -INF, 0 };
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i].first;
		a[i].second = i;
	}
	a.resize(1ll << h);
	for (int i = n + 1; i < a.size(); i++)
	{
		a[i].first = -INF;
		a[i].second = i;
	}
	n = 1 << h;
	init(a, tree, 1, 0, n - 1);

	cin >> m;
	for (int i = 0; i < m; i++)
	{
		ll q;
		cin >> q;
		if (q == 1)
		{
			ll index, value;
			cin >> index >> value;
			update(tree, index, { value, index });
		}
		else if (q == 2)
		{
			int l, r;
			cin >> l >> r;
			pair<ll, ll> ai = getMax(tree, 1, 0, n - 1, l, r);
			pair<ll, ll> aj = max(getMax(tree, 1, 0, n - 1, l, ai.second - 1), getMax(tree, 1, 0, n - 1, ai.second + 1, r));
			cout << ai.first + aj.first << '\n';
		}
	}

	return 0;
}