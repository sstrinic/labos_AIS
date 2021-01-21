#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Cutoff 20

void Test(int);
void GenerateArray(int*, int*, int);
void Reset(int*, int*, int);
void ShellSort(int*, int);
void QuickSort(int*, int, int, int);
int Sred3(int*, int, int);
void InsertionSort(int*, int);
void MergeSort(int*, int);
void MSort(int*, int*, int, int);
void Merge(int*, int*, int, int, int);
void Swap(int*, int, int);

int main()
{
	srand((unsigned)time(NULL));

	Test(100);
	Test(1000);
	Test(10000);
	Test(100000);

	return 0;
}

void Test(int number)
{
	int* arr;
	int* arrCpy;

	clock_t start;
	clock_t end;
	double timeSpent = 0.0;

	arr = (int*)malloc(number * sizeof(int));
	if (arr == NULL) {
		printf("\nGRESKA U ALOKACIJI!!!\n");
		return;
	}

	arrCpy = (int*)malloc(number * sizeof(int));
	if (arrCpy == NULL) {
		printf("\nGRESKA U ALOKACIJI!!!\n");
		return;
	}

	GenerateArray(arr, arrCpy, number);

	//SHELL
	printf("\n SHELL \n");
	start = clock();
	ShellSort(arr, number);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);
	Reset(arr, arrCpy, number);

	//QUICK
	printf("\n QUICK \n");
	start = clock();
	QuickSort(arr, number,0,number-1);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);
	Reset(arr, arrCpy, number);

	//MERGE
	printf("\n MERGE \n");
	start = clock();
	MergeSort(arr, number);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);
	Reset(arr, arrCpy, number);

	free(arr);
	free(arrCpy);
}

void GenerateArray(int* arr, int* arrB, int n)
{
	for (int i = 0; i < n; i++)
		arr[i] = arrB[i] = rand();
}

void Reset(int* arr, int* arrB, int n)
{
	for (int i = 0; i < n; i++)
		arr[i] = arrB[i];
}

void ShellSort(int* X, int N)
{
	int h,i, j,temp;
	for(h = N/2; h > 0; h = h/2)
		for (i = h; i < N; i++)
		{
			temp = X[i];
			for (j = i; j >= h; j -= h)
				if (temp < X[j - h])
					X[j] = X[j - h];
				else
					break;
			X[j] = temp;
		}	
}

void QuickSort(int* X, int N, int L, int D)
{
	static int a = 0;
	int i, j, S;

	if (L + Cutoff < D)
	{
		S = Sred3(X, L, D);
		i = L;
		j = D;

		for (;;)
		{
			while (X[++i] < S) {}
			while (X[--j] > S) {}
			if (i < j) Swap(X, i, j);
			else
				break;
		}
		Swap(X, i, D);
		QuickSort(X, N, L, i - 1);
		QuickSort(X, N, i + 1, D);
	}
	else
		InsertionSort(&X[L], D - L + 1);
}

int Sred3(int* X, int L, int D)
{
	int S = (L + D) / 2;

	if (X[L] > X[S])
		Swap(X, L, S);
	if (X[L] > X[D])
		Swap(X, L, D);
	if (X[S] > X[D])
		Swap(X, S, D);

	Swap(X, S, D);
	return X[D];
}

void InsertionSort(int* X, int N)
{
	int i, j, temp;
	for (i = 1; i < N; i++)
	{
		temp = X[i];
		j = i - 1;
		while (j >= 0 && temp < X[j])
		{
			X[j + 1] = X[j];
			j--;
		}
		X[j + 1] = temp;
	}
}

void MergeSort(int* X, int N)
{
	int* pC;
	pC = (int*)malloc(N * sizeof(int));
	if (pC != NULL)
	{
		MSort(X, pC, 0, N - 1);
		free(pC);
	}
	else
		printf("\n GRESKA ALOKACIJE!!\n");
}

void MSort(int* X, int* C, int L, int D)
{
	int S;
	if (L < D)
	{
		S = (L + D) / 2;
		MSort(X, C, L, S);
		MSort(X, C, S + 1, D);
		Merge(X, C, L, S + 1, D);
	}
}

void Merge(int* A,int* C, int pL,int pD, int kD)
{
	int i, kL, brEl, tempPoz;

	kL = pD - 1;
	tempPoz = pL;
	brEl = kD - pL + 1;

	while (pL <= kL && pD <= kD)
		if (A[pL] <= A[pD])
			C[tempPoz++] = A[pL++];
		else
			C[tempPoz++] = A[pD++];

	while (pL <= kL)
		C[tempPoz++] = A[pL++];

	while (pD <= kD)
		C[tempPoz++] = A[pD++];

	for (i = 0; i < brEl; i++, kD--)
		A[kD] = C[kD];
}

void Swap(int* X, int x, int y)
{
	int temp;
	temp = X[x];
	X[x] = X[y];
	X[y] = temp;
}