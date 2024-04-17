#include<iostream>
#include<vector>
#include<math.h>
#include<complex>
#include<string>
#include<algorithm>

using namespace std;
typedef complex<double> cpx;
const double PI = acos(-1);

/*FFT, �ռ��� �ҽ��ڵ� ��ó
https://m.blog.naver.com/PostView.nhn?blogId=kks227&logNo=221633584963&proxyReferer=https%3A%2F%2Fwww.google.com%2F
*/


//FFT
void FFT(vector<cpx>& f, cpx w) {
	int n = f.size();
	if (n == 1) return;

	vector<cpx> even(n / 2), odd(n / 2);
	for (int i = 0; i < n; ++i) (i % 2 ? odd : even)[i / 2] = f[i];

	FFT(even, w * w);
	FFT(odd, w * w);

	cpx wp(1, 0);
	for (int i = 0; i < n / 2; ++i) {
		f[i] = even[i] + wp * odd[i];
		f[i + n / 2] = even[i] - wp * odd[i];
		wp *= w;
	}
}

//�ռ���:���� a,b�� �޾Ƽ� ũ�Ⱑ (a,b�� ũ�⺸�� ū 2�� �������� ���� ���� ��*2)�� �ռ����� ��ȯ��
vector<int> poly_multiply(vector<int> A, vector<int> B) {

	vector<cpx> a(A.begin(), A.end());		//convert int vector to complex vector 
	vector<cpx> b(B.begin(), B.end());

	int n = 1;
	int aSize = a.size();
	int bSize = b.size();
	while (n < aSize || n < bSize) n *= 2;
	n *= 2;

	vector<cpx> c(n); a.resize(n); b.resize(n);

	cpx w = cpx(cos((2 * PI) / n), sin((2 * PI / n)));
	FFT(a, w); FFT(b, w);

	for (int i = 0; i < n; ++i) {
		c[i] = a[i] * b[i];
	}

	FFT(c, cpx(1, 0) / w);   //IFFT
	for (int i = 0; i < n; ++i) {
		c[i] /= n;
	}

	vector<int> ret(n);
	for (int i = 0; i < n; i++) {
		ret[i] = (int)round(c[i].real());
	}
	return ret;										//cpx�� �����ϰ� int�� �ٲ㼭 int�� ���� 
}

int main() {

	int a, b = 0;
	cin >> a >> b;                                    //a,b �� ũ�� �Է�

	vector<int> f(a + 1), g(b + 1);                   //f(x),g(x) ����
	for (int i = 0; i < a + 1; ++i) cin >> f[i];
	for (int i = 0; i < b + 1; ++i) cin >> g[i];           //f(x),g(x) �Է�

	vector<int> h = poly_multiply(f, g);           //h(x) = f(x)*g(x) 

	int ret = 0;                                  //��°�, XOR�� �׵�� 0���� �ʱ�ȭ
	for (auto elem : h) ret ^= elem;               //���ҵ��� XOR����

	cout << ret;                                    //��°� ���


	return 0;
}
