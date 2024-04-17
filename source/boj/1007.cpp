#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

// ó�� �־����� picked�� {}

void pick(int n, vector<int> xVector, vector<int> yVector, vector<int>& picked, int toPick, double& min)
{
	// �� �� �� ������ �� ����� +, �� �� ����� -
	if (toPick == 0)
	{
		int tempX = 0; int tempY = 0;
		for (int i = 0; i < picked.size() * 2; i++)
		{
			if (find(picked.begin(), picked.end(), i) != picked.end())
			{
				tempX += xVector[i];
				tempY += yVector[i];
			}
			else
			{
				tempX -= xVector[i];
				tempY -= yVector[i];
			}
		}

		double temp = pow((double)tempX * (double)tempX + (double)tempY * (double)tempY, 0.5);
		if (temp < min)
			min = temp;

		return;
	}

	int smallest = picked.empty() ? 0 : picked.back();

	for (int next = smallest; next < n; next++)
	{
		if (find(picked.begin(), picked.end(), next)  == picked.end())
		{
			picked.push_back(next);
			pick(n, xVector, yVector, picked, toPick - 1, min);
			picked.pop_back();
		}
	}
}

int main(void)
{

	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int N;
		double min = 1000000000.0;
		cin >> N;
		vector<int> emptySet;
		vector<int> xVector, yVector;
		int tempX, tempY;

		for (int i = 0; i < N; i++)
		{
			cin >> tempX >> tempY;
			xVector.push_back(tempX);
			yVector.push_back(tempY);
		}

		pick(N, xVector, yVector, emptySet, N / 2, min);
		printf("%f\n", min);
	}
	return 0;
}