#include <iostream>
#include <map>
#include <algorithm>

typedef long long ll;

using namespace std;

int main(void)
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	bool isRoot = true;
	map<ll, ll> node;
	ll N, C = 0;
	cin >> N;

	node.insert({ 0, 0 });
	node.insert({ 300001, 0 });

	for (int n = 0; n < N; n++)
	{
		int key;
		cin >> key;
		node.insert({ key, 0 });
		auto iter = node.find(key);
		auto r_iter = iter;
		auto l_iter = iter;


		// ��Ʈ key�� value := 0
		if (isRoot)
		{
			isRoot = false;
		}

		// �׷��� ������ �ش� key�� value := ���� ����� ����� value + 1
		else
		{
			l_iter--;
			r_iter++;
			node[key] = max(l_iter->second + 1, r_iter->second + 1);
		}

		C += node[key];
		cout << C << '\n';
		
	}
	
	return 0;
}