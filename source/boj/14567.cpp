#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(void)
{
	vector<int> pre(1001);				// pre[i] := ���������� ����
	vector<vector<int>> suc(1001);		// suc[i] := �ļ����� ��ȣ�� ��Ƶа�
	vector<int> time(1001, 1);

	int N, M;							// N := �� ���� ����, M := ���� ������ ��
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		int tempPre, tempSuc;
		cin >> tempPre >> tempSuc;
		suc[tempPre].push_back(tempSuc);
		pre[tempSuc]++;
	}

	vector<int> result(1001);

	queue<int> q;

	for (int i = 1; i <= N; i++)
	{
		if (!pre[i])
		{
			q.push(i);
		}
	}

	while (!q.empty())
	{
		int n = q.front();
		q.pop();

		for (int i = 0; i < suc[n].size(); i++)
		{
			result[suc[n][i]] = max(result[suc[n][i]], result[n] + time[n]);
			pre[suc[n][i]]--;
			if (pre[suc[n][i]] == 0)
			{
				q.push(suc[n][i]);
			}
		}
	}


	for (int i = 1; i <= N; i++)
	{
		cout << result[i] + time[i] << ' ';
	}




	return 0;
}