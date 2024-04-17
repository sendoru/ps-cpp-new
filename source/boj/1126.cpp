#include <iostream>
#include <vector>
constexpr int MAX = 500'001;
using namespace std;

int main(void)
{
	int n;
	cin >> n;
	vector<int> blocks(n);
	// dp[i] := �������� i�� ��, �� �� �� ���� ���� �ִ� ����
	vector<int> dp(MAX, -1);
	for (int i = 0; i < n; i++)
		cin >> blocks[i];
	
	for (int i = 0; i < n; i++)
	{
		// ������ �׾Ƶ״� �͵鿡�� i��° ����� �� �߰��ϴ� ���
		vector<int> dpTemp = dp;
		for (int j = 0; j < MAX; j++)
		{
			if (dp[j] == -1) continue;
			// �� ���� �ʿ� �״� ���
			dpTemp[j + blocks[i]] = max(dpTemp[j + blocks[i]], dp[j] + blocks[i]);
			// �� ���� �ʿ� �״� ���
			dpTemp[abs(j - blocks[i])] = max(dpTemp[abs(j - blocks[i])], max(dp[j], dp[j] - j + blocks[i]));
		}
		// i��° ��� �ϳ��� ���� ���
		dpTemp[blocks[i]] = max(dpTemp[blocks[i]], blocks[i]);
		dp = dpTemp;
	}
	
	cout << dp[0];
	return 0;
}