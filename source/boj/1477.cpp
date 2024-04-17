#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main(void)
{
	int n, m, l;
	cin >> n >> m >> l;
	vector<int> rest(n);
	for (int i = 0; i < n; i++)
	{
		cin >> rest[i];
	}
	rest.push_back(0);
	rest.push_back(l);
	sort(rest.begin(), rest.end());
	int pLeft = 0, pRight = l, ans = l;
	// �̰Ը���
	while (pLeft <= pRight)
	{
		if (pRight == 0)
		{
			ans = 1;
			break;
		}
		int mid = (pRight + pLeft) / 2, cnt = 0;
		// cnt := �ִ� �Ÿ��� �ּڰ��� mid�� ����� ���� �ʿ��� �ּ����� �ްԼ� ����
		for (int i = 1; i < rest.size(); i++)
		{
			cnt += (rest[i] - rest[i - 1] - 1) / mid;
		}
		// �ִ� �Ÿ��� �ּڰ��� mid ���Ϸ� ����� ���� ������ �ϴ� �ްԼ� ������ m������ ���� ��
		if (cnt > m)
		{
			pLeft = mid + 1;
		}
		// m�� ������ �ްԼҷ� �ִ� �Ÿ��� �ּڰ��� mid ���Ϸ� ���� �� ���� ��
		else
		{
			ans = min(ans, mid);
			pRight = mid - 1;
		}
	}
	cout << ans;
	return 0;
}