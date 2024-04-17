#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int N, M, initialDrill;

int solve(vector<string>& map, vector<vector<vector<int> > >& visit, int initialDrill)
{
	queue<vector<int> > q;

	// ��(y��ǥ), ��(x��ǥ), ���� �μ� �� �ִ� Ƚ��, ����� ����
	q.push({ 0, 0, initialDrill, 1 });
	int row, col, drill, dist;

	while (!q.empty())
	{

		row = q.front()[0];
		col = q.front()[1];
		drill = q.front()[2];
		dist = q.front()[3];

		// ������ �����ϸ� ����
		if (row == N - 1 && col == M - 1)
		{
			return dist;
		}

		// ��
		if (row > 0)
		{
			if (map[row - 1][col] == '0' && visit[row - 1][col][drill] == 0)
			{
				visit[row - 1][col][drill] = dist + 1;
				q.push({ row - 1, col, drill, dist + 1 });
			}
			else if (map[row - 1][col] == '1' && drill > 0 && visit[row - 1][col][drill - 1] == 0)
			{
				visit[row - 1][col][drill - 1] = dist + 1;
				q.push({ row - 1, col, drill - 1, dist + 1 });
			}
		}

		// �Ʒ�
		if (row < N - 1)
		{
			if (map[row + 1][col] == '0' && visit[row + 1][col][drill] == 0)
			{
				visit[row + 1][col][drill] = dist + 1;
				q.push({ row + 1, col, drill, dist + 1 });
			}
			else if (map[row + 1][col] == '1' && drill > 0 && visit[row + 1][col][drill - 1] == 0)
			{
				visit[row + 1][col][drill - 1] = dist + 1;
				q.push({ row + 1, col, drill - 1, dist + 1 });
			}
		}

		// ����
		if (col > 0)
		{
			if (map[row][col - 1] == '0' && visit[row][col - 1][drill] == 0)
			{
				visit[row][col - 1][drill] = dist + 1;
				q.push({ row, col - 1, drill, dist + 1 });

			}
			else if (map[row][col - 1] == '1' && drill > 0 && visit[row][col - 1][drill - 1] == 0)
			{
				visit[row][col - 1][drill - 1] = dist + 1;
				q.push({ row, col - 1, drill - 1, dist + 1 });
			}
		}

		// ������
		if (col < M - 1)
		{
			if (map[row][col + 1] == '0' && visit[row][col + 1][drill] == 0)
			{
				visit[row][col + 1][drill] = dist + 1;
				q.push({ row, col + 1, drill, dist + 1 });
			}
			else if (map[row][col + 1] == '1' && drill > 0 && visit[row][col + 1][drill - 1] == 0)
			{
				visit[row][col + 1][drill - 1] = dist + 1;
				q.push({ row, col + 1, drill - 1, dist + 1 });
			}
		}

		q.pop();
	}

	return -1;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> initialDrill;

	vector<string> map(N);
	vector<vector<vector<int> > > visit(N, vector<vector<int> >(M, vector<int>(initialDrill + 1, 0)));
	visit[0][0][initialDrill] = 1;

	for (int i = 0; i < N; i++)
	{
		cin >> map[i];
	}

	int ans = solve(map, visit, initialDrill);
	cout << ans << '\n';

	return 0;
}