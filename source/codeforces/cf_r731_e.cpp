#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1ll << 60;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int q;
	cin >> q;
	while (q--)
	{
		int n, k;
		cin >> n >> k;
		// temper[i][0] := i��° ��ġ���� �ڱ� ��ġ�� �ִ� �������� ���� �µ�
		// temper[i][1] := i��° ��ġ���� �ڱ� �����ʿ� �ִ� �������� ���� �µ�
		// temper[i][2] := i��¹ ��ġ���� �ڱ� ���ʿ� �ִ� �������� ���� �µ�
		vector<vector<ll>> temper(n + 1, vector<ll>(3, INF));
		// �µ�, ��ġ
		vector<pair<ll, ll>> aircons(k);
		for (int i = 0; i < k; i++)
		{
			cin >> aircons[i].second;
		}
		for (int i = 0; i < k; i++)
		{
			cin >> aircons[i].first;
			temper[aircons[i].second][0] = aircons[i].first;
		}
		// 2������ �Ⱦ��ָ� ���� �������� ���� �ּҿµ� ���ϱ�
		for (int i = 2; i <= n; i++)
		{
			temper[i][2] = min(temper[i - 1][2] + 1, temper[i - 1][0] + 1);
		}
		// n - 1������ ������ �������� ���� �ּҿµ� ���ϱ�
		for (int i = n - 1; i >= 1; i--)
		{
			temper[i][1] = min(temper[i + 1][1] + 1, temper[i + 1][0] + 1);
		}
		for (int i = 1; i <= n; i++)
		{
			cout << min(temper[i][0], min(temper[i][1], temper[i][2])) << ' ';
		}
		cout << '\n';
	}
	return 0;
}