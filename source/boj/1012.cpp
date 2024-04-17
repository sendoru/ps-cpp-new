#include <iostream>
#define INF 0x7fffffff

using namespace std;

bool farm[50][50] = { 0, };
bool visited[50][50] = { 0, };

// ��, ��, ��, ��
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0, 0 };

void dfs(int x, int y, int m, int n)
{
	visited[y][x] = true;

	for (int i = 0; i < 4; i++)
	{
		int newX = x + dx[i];
		int newY = y + dy[i];

		// �迭�� �ε����� ��� �� ����ó��
		if (newX < 0 || newY < 0 || newX >= m || newY >= n)
		{
			continue;
		}

		// ���߰� �ɾ��� ���� �ʰų� �����������̰� �̹� �湮�� ��ġ�� �ǳʶٱ�
		if (!farm[newY][newX] || visited[newY][newX])
		{
			continue;
		}

		dfs(newX, newY, m, n);
	}
}

int main(void)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		int M, N, K;
		cin >> M >> N >> K;
		for (int k = 0; k < K; k++)
		{
			int x, y;
			cin >> x >> y;
			farm[y][x] = true;
		}
		int cnt = 0;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < M; x++)
			{
				if (farm[y][x] && !visited[y][x])
				{
					dfs(x, y, M, N);
					cnt++;
				}
			}
		}
		cout << cnt << endl;

		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				farm[i][j] = 0;
				visited[i][j] = 0;
			}
		}
	}
	
	return 0;
}