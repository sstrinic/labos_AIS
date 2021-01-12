#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Test(int);
void GenerateArray(int*, int* ,int);
void Reset(int*, int*, int);
void ExchangeSort(int*, int);
void SelectionSort(int*, int);
void InsertionSort(int*, int);
void BubbleSort(int*, int);
void Swap(int*,int,int);

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

	arr = (int*) malloc(number * sizeof(int));
	if (arr == NULL) {
		printf("\nGRESKA U ALOKACIJI!!!\n");
		return;
	}
		
	arrCpy = (int*) malloc(number * sizeof(int));
	if (arrCpy == NULL) {
		printf("\nGRESKA U ALOKACIJI!!!\n");
		return;
	}

	GenerateArray(arr, arrCpy, number);

	//Exchange
	printf("\n EXCHANGE \n");
	start = clock();
	ExchangeSort(arr, number);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);
	Reset(arr, arrCpy, number);

	//Selection
	printf("\n SELECTION \n");
	start = clock();
	SelectionSort(arr, number);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);
	Reset(arr, arrCpy, number);

	//Insertion
	printf("\n iNSERTION \n");
	start = clock();
	InsertionSort(arr, number);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);
	Reset(arr, arrCpy, number);

	//Bubble
	printf("\n BUBBLE \n");
	start = clock();
	BubbleSort(arr, number);
	end = clock();
	timeSpent = ((double)end - start) / CLOCKS_PER_SEC;
	printf("Vrijeme potrebno za %d elemenata: %lf sec\n", number, timeSpent);

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

void ExchangeSort(int* X, int N)
{
	int i, j;
	for (i = 0; i < N - 1;i++)
		for (j = i + 1; j < N; j++)
			if (X[j] < X[i])
				Swap(X, i, j);
}

void SelectionSort(int* X, int N)
{
	int i, j, min;
	for (i = 0; i < N - 1; i++)
	{
		min = i;
		for (j = min + 1; j < N; j++)
			if (X[j] < X[min])
				min = j;
	}
}

void InsertionSort(int* X, int N)
{
	int i, j, temp;
	for (i = 1; i < N; i++)
	{
		temp = X[i];
		j = i - 1;
		while (j >= 0 && temp<X[j])
		{
			X[j + 1] = X[j];
			j--;
		}
		X[j + 1] = temp;
	}
}

void BubbleSort(int* X, int N)
{
	int i, j;
	for (i = 0; i < N - 1; i++)
		for (j = N-1; j > i; j--)
			if (X[j-1] > X[j])
				Swap(X, j-1, j);
}

void Swap(int* X, int x, int y)
{
	int temp;
	temp = X[x];
	X[x] = X[y];
	X[y] = temp;
}