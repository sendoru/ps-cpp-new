#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <queue>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll n;
	cin >> n;
	// �׳� 1�� n�� �������� �ִ� ���� ��������
	// �׷� x�� 2�� n�� �������� �ִ� ���� �����ϸ� �ƹ�ư �ȴ�.
	cout << 2 * n << '\n';
	// 1�� n�� ���� -> 4�� floor(n/4)�� ����, �� ���� ���� n mod 4
	if (n % 4 != 0)
		cout << n % 4;
	for (int i = 0; i < n / 4; i++)
		cout << 4;
	cout << '\n';
	return 0;
}