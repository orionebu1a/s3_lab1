#pragma once

struct Matrix {
	int * cumulateNoZero;
	int * rowPosition;
	double * value;
	int m;
	int n;
	int k;
};