//#include <vld.h>
#include <iostream>
#include "matrix.h"
#include "inout.h"
#define nMax 100000
#define mMax 100000
using namespace std;

int copyMatrix(Matrix * M1, Matrix * M2) {
	M2->cumulateNoZero = (int *)new int[M1->m];
	memcpy(M2->cumulateNoZero, M1->cumulateNoZero, (M1->m) * sizeof(int));
	M2->rowPosition = (int *)new int[M1->k];
	memcpy(M2->rowPosition, M1->rowPosition, (M1->k) * sizeof(int));
	M2->value = (double *)new double[M1->k];
	memcpy(M2->value, M1->value, (M1->k) * sizeof(double));
	M2->k = M1->k;
	M2->n = M1->n;
	M2->m = M1->m;
	return 0;
}

int action(Matrix * M1, Matrix * M2) {
	for (int i = 0; i < M1->k; i++) {
		M2->rowPosition[i] = (M1->n - 1) - M2->rowPosition[i];
	}
	return 0;
}

int main() {
	Matrix M, M_changed;
	if (input(mMax, nMax, &M) == 1) {
		cout << "wrong input";
		return 1;
	}
	copyMatrix(&M, &M_changed);
	action(&M, &M_changed);
	printMatrix(&M);
	printMatrix(&M_changed);
	clearMatrix(&M_changed);
	clearMatrix(&M);
	return 0;
}