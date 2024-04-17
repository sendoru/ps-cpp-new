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

pair<ll, ll> min(pair<ll, ll> a, pair<ll, ll> b)
{
	if (a.first < b.first)
	{
		return a;
	}
	if (a.first > b.first)
	{
		return b;
	}
	if (a.second < b.second)
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
		return tree[node] = min(init(a, tree, node * 2, start, (start + end) / 2), init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end));
	}
}

// left, right: �ּڰ��� ���ϴ� ������ left ~ right
// ������ ���ڴ� init�� �Ȱ���
pair<ll, ll> min(vector<pair<ll, ll> >& tree, int node, int start, int end, int left, int right)
{
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start)
	{
		return { INF, -1 };
	}
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end)
	{
		return tree[node];
	}
	return min(min(tree, node * 2, start, (start + end) / 2, left, right), min(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

void update(vector<pair<ll, ll> >& tree, int index, pair<ll, ll> newValue)
{
	int node = tree.size() / 2 + index;
	tree[node] = newValue;
	node /= 2;
	while (node != 0)
	{
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
		node /= 2;
	}
}

int main()
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);


	int N, M, temp;
	string ans = "";
	cin >> N;
	int h = (int)ceil(log2(N));
	int treeSize = 1 << (h + 1);
	vector<pair<ll, ll> > a(N);
	vector<pair<ll, ll> > tree(treeSize);

	for (int i = 0; i < N; i++)
	{
		cin >> a[i].first;
		a[i].second = i;
	}
	a.resize(1ll << h);
	for (int i = N; i < a.size(); i++)
	{
		a[i].first = INF;
		a[i].second = i;
	}
	N = 1 << h;
	init(a, tree, 1, 0, N - 1);

	cin >> M;
	for (int i = 0; i < M; i++)
	{
		ll q1, q2, q3;
		cin >> q1;
		if (q1 == 1)
		{
			cin >> q2 >> q3;
			q2--;
			a[q2] = { q3, q2 };
			update(tree, q2, a[q2]);
		}
		else if (q1 == 2)
		{
			cin >> q2 >> q3;
			cout << min(tree, 1, 0, N - 1, q2 - 1, q3 - 1).second + 1 << '\n';
		}
	}

	return 0;
}