#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vector<int> squares;
	int len = 0;
	while (len * len <= 5000)
	{
		squares.push_back(len * len);
		len++;
	}
	int t;
	cin >> t;
	while (t--)
	{
		int s;
		cin >> s;
		// � �Ƹ��ٿ� ���� a�� ���� a_s��� ���� a_s - 1�� �Ƹ��ٿ� ������ ���� (a_s > 1�϶�)
		// ���̰� l�� �Ƹ��ٿ� ������ �ִ��� 1 + 3 + 5 + ... + (2l - 1) = l^2
		int ans = lower_bound(squares.begin(), squares.end(), s) - squares.begin();
		cout << ans << '\n';
	}
	return 0;
}