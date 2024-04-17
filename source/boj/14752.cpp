#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;

int main(void)
{
	int n;
	cin >> n;
	vector<pair<ll, ll>> labeled(n);
	for (int i = 0; i < n; i++) cin >> labeled[i].first;
	for (int i = 0; i < n; i++) cin >> labeled[i].second;
	sort(labeled.begin(), labeled.end());

	// dp[i][0] := i��° ���� �� �������� ��, i + 1 ~ ������ �� �߿� ���� ���� ������ �ּڰ�
	// dp[i][1] := i��° ���� �������� ��, i + 1 ~ ������ �� �߿� ���� ���� ������ �ּڰ�
	vector<vector<ll>> dp(n, vector<ll>(2));
	ll ans = n;
	for (int i = n - 2; i >= 0; i--)
	{
		int dist = labeled[i + 1].first - labeled[i].first;
		if (dist >= labeled[i].second + 1)
		{

		}
		else
		{

		}
	}
}