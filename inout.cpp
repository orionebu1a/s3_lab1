#include <iostream>
#include "matrix.h"
using namespace std;

int input(int mMax, int nMax, Matrix * M) {
	int m, n, k, icoord, jcoord;
	double value;
	cout << "Please, print number of lines:" << endl;
	cin >> m;
	if (!cin.good()) {
		return 1;
	}
	cout << "Please, print number of columns:" << endl;
	cin >> n;
	if (!cin.good()) {
		return 1;
	}
	if (m > mMax) {
		cout << "error";
	}
	//—жатое хранение строкой (Compressed Sparse Row, CSR)
	if (n > nMax) {
		cout << "error";
	}
	cout << "Please, print number of non-null elements:" << endl;
	cin >> k;
	if (!cin.good()) {
		return 1;
	}
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
		if (!cin.good()) {
			return 1;
		}
		cin >> jcoord;
		if (!cin.good()) {
			return 1;
		}
		if (icoord >= m || jcoord >= n) {
			cout << "too big index" << endl;
			return 1;
		}
		cin >> value;
		if (!cin.good()) {
			return 1;
		}
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

template <typename MyType>
int coutLine(MyType * str, int len) {
	for (int i = 0; i < len; i++) {
		cout << str[i] << " ";
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
	cout << endl;
	int delta, quantity;
	double * str;
	for (int i = 0; i < M->m; i++) {
		if (i == 0) {
			delta = 0;
			quantity = M->cumulateNoZero[i];
		}
		else {
			delta = M->cumulateNoZero[i - 1];
			quantity = M->cumulateNoZero[i] - M->cumulateNoZero[i - 1];
		}
		str = (double *)new double[M->n];
		for (int j = 0; j < M->n; j++) {
			str[j] = 0;
		}
		for (int j = delta; j < delta + quantity; j++) {
			str[M->rowPosition[j]] = M->value[j];
		}
		coutLine(str, M->n);
		delete [] str;
	}
	cout << endl;
	return 0;
}

int clearMatrix(Matrix * M) {
	delete [] M->cumulateNoZero;
	delete [] M->rowPosition;
	delete [] M->value;
	return 0;
}