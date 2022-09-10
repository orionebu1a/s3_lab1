#include <iostream>
template <typename MyType>
using namespace std;

int input(int mMax, int nMax, Matrix * M) {
	int m, n, k, icoord, jcoord;
	double value;
	cout << "Please, print number of lines:" << endl;
	cin >> m;
	cout << "Please, print number of columns:" << endl;
	cin >> n;
	if (m > mMax) {
		cout << "error";
	}
	//—жатое хранение строкой (Compressed Sparse Row, CSR)

	if (n > nMax) {
		cout << "error";
	}
	cout << "Please, print number of non-null elements:" << endl;
	cin >> k;
	M->m = m;
	M->n = n;
	M->k = k;
	cout << "Please, print all elements in format: i, j, value" << endl;
	M->cumulateNoZero = (int *)new int[m];
	M->rowPosition = (int *)new int[k];
	M->value = (double *)new double[k];
	for (int i = 0; i < m; i++) {
		(M->cumulateNoZero)[i] = 0;
	}
	for (int i = 0; i < k; i++) {
		cin >> icoord;
		cin >> jcoord;
		if (icoord >= m || jcoord >= n) {
			cout << "too big index" << endl;
			return 0;
		}
		cin >> value;
		(M->cumulateNoZero)[icoord] = (M->cumulateNoZero)[icoord] + 1;
		(M->rowPosition)[i] = jcoord;
		(M->value)[i] = value;
	}
	//compressing
	int sum = 0;
	for (int i = 0; i < m; i++) {
		sum = sum + (M->cumulateNoZero)[i];
		(M->cumulateNoZero)[i] = sum;
	}
	return 0;
}

int coutLine(MyType * str, int len) {
	for (int i = 0; i < len; i++) {
		cout << str[i];
	}
	cout << endl;
	return 0;
}

int output(Matrix * M) {
	coutLine(M->cumulateNoZero, M->m);
	coutLine(M->rowPosition, M->k);
	coutLine(M->value, M->k);
	return 0;
}

int printMatrix(Matrix * M) {

	return 0;
}