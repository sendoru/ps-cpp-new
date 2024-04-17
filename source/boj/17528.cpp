#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int INF = 0x3fffffff;

int main(void)
{
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++)
		cin >> a[i] >> b[i];

	// dp[i][j] : i�� ������� ������ �۾� ��ȣ, j�� a�� �Ҹ��� �ð�, dp[i][j]�� b�� �Ҹ��� �ð��� �ּڰ�
	vector<vector<int>> dp(n + 1, vector<int>(250 * n + 1, INF));
	dp[0][a[0]] = 0;
	dp[0][0] = b[0];
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < dp[i].size(); j++)
		{
			if (dp[i - 1][j] == INF)
				continue;
			// ���� �۾��� a������ ó���Ҷ�
			dp[i][j + a[i]] = dp[i - 1][j];
			// ���� �۾��� b������ ó���� ��
			dp[i][j] = dp[i - 1][j] + b[i];
		}
	}

	int ans = INF;
	for (int i = 0; i < dp[n - 1].size(); i++)
		if (max(i, dp[n - 1][i]) < ans)
			ans = max(i, dp[n - 1][i]);

	cout << ans;
	return 0;
}