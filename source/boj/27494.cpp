/*

#include <iostream>
#define MOD 1000000
using namespace std;

int main() {
	long long int N;
	cin >> N;

	int p = 15 * MOD / 10; // �ǻ�� �ֱ�
	int* fib = new int[p + 1];
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; i < p; i++)
		fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;

	cout << fib[N % p] << endl;

	return 0;
}
*/



#include <iostream>
#include <vector>
#define MOD 1000000
using namespace std;

int main() {
	long long N;
	cin >> N;

	int p;//�Ǻ���ġ�� �ֱ�
	vector<int> fib(2);
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; true; i++) {
		fib.push_back((fib[i - 1] + fib[i - 2]) % MOD);
		if (i > 3 && fib[i - 1] == 1 && fib[i - 2] == 0)
		{
			p = fib.size() - 3;
			break;
		}
	}

	cout << fib[N % p] << endl;

	return 0;
}

