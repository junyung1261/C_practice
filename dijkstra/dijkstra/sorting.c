#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void insertionSort(int *arr, int len);
void mergeSort(int *arr, int len);
void selectionSort(int *arr, int len);
void quickSort(int *arr, int left, int right);
void shellSort(int *arr, int len);




int main(int argc, char *argv[]) {



	int startTime, exeTime;
	int ok, num = 0, count = 0;
	int i;

	FILE *fp;

	fp = fopen(argv[1], "r");

	fscanf(fp, "%d", &num);
	i = num;
	int *input = (int*)malloc(sizeof(int)*i);

	while (1) {
		ok = fscanf(fp, "%d", &num);
		if (ok == EOF) break;

		input[count++] = num;
	}
	fclose(fp);

	printf("tested array size is = %d \n", count);

	/*--------calling the insertion sort--------*/
	startTime = clock();
	insertionSort(input, count);
	exeTime = clock() - startTime;
	printf("insertion time : %dms\n", exeTime / 1000);

	/*--------calling the merge sort--------*/
	int *copy = (int*)malloc(sizeof(int)*count);
	memmove(copy, input, sizeof(int)*count);

	startTime = clock();
	mergeSort(copy, count);
	exeTime = clock() - startTime;
	printf("merge time : %dms\n", exeTime / 1000);
	free(copy);

	/*--------calling the quick sort--------*/
	copy = (int*)malloc(sizeof(int)*count);
	memmove(copy, input, sizeof(int)*count);

	startTime = clock();
	quickSort(input, 0, count - 1);
	exeTime = clock() - startTime;
	printf("quick time : %dms\n", exeTime / 1000);
	free(copy);

	/*--------calling the shell sort--------*/
	startTime = clock();
	shellSort(input, count);
	exeTime = clock() - startTime;
	printf("shell time : %dms\n", exeTime / 1000);

	/*--------calling the selection sort--------*/
	startTime = clock();
	selectionSort(input, count);
	exeTime = clock() - startTime;
	printf("seleciton time : %dms\n", exeTime / 1000);



	free(input);
}


void insertionSort(int *arr, int len) {
	int *copy = (int*)malloc(sizeof(int)*len);
	memmove(copy, arr, sizeof(int)*len);


	int i, j;
	int key;
	for (i = 1; i < len; i++)
	{
		key = copy[i];
		for (j = i - 1; j >= 0 && copy[j]>key; j--)
			copy[j + 1] = copy[j];
		copy[j + 1] = key;

	}
	free(copy);
}

void mergeSort(int *arr, int len) {

	if (len < 2) return 0;

	int mid = len / 2;
	mergeSort(arr, mid);
	mergeSort(arr + mid, len - mid);

	int *temp = (int*)malloc(sizeof(int)*len);
	int i = 0;
	int j = mid;
	int k = 0;
	while (i < mid && j < len)		//
		temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
	while (i < mid)
		temp[k++] = arr[i++];
	while (j < len)
		temp[k++] = arr[j++];

	for (i = 0; i < len; i++) {
		arr[i] = temp[i];


	}

	free(temp);
}

void selectionSort(int *arr, int len)
{

	int *copy = (int*)malloc(sizeof(int)*len);
	memmove(copy, arr, sizeof(int)*len);

	int i, j;
	int min, temp;
	for (i = 0; i<len - 1; i++) {
		min = i;
		for (j = i + 1; j<len; j++) {
			if (copy[j] < copy[min]) min = j;
		}
		temp = copy[i];
		copy[i] = copy[min];
		copy[min] = temp;
	}
	free(copy);
}


void quickSort(int *arr, int left, int right)
{
	int pivot, l_hold, r_hold;
	l_hold = left;
	r_hold = right;
	pivot = arr[left];
	while (left < right)
	{

		while ((arr[right] >= pivot) && (left < right))
			right--;


		if (left != right)
		{
			arr[left] = arr[right];
		}

		while ((arr[left] <= pivot) && (left < right))
			left++;

		if (left != right)
		{
			arr[right] = arr[left];
			right--;
		}
	}


	arr[left] = pivot;
	pivot = left;
	left = l_hold;
	right = r_hold;


	if (left < pivot)
		quickSort(arr, left, pivot - 1);
	if (right > pivot)
		quickSort(arr, pivot + 1, right);
}


void shellSort(int *arr, int len)
{

	int *copy = (int*)malloc(sizeof(int)*len);
	memmove(copy, arr, sizeof(int)*len);

	int i, j, m, temp;
	int k = len;
	do {
		k = k / 3 + 1;

		for (m = 0; m<k; m++) {
			for (i = m + k; i<len; i += k) {

				temp = copy[i];
				for (j = i - k; copy[j] > temp && j >= 0; j -= k) {
					copy[j + k] = copy[j];
				}
				copy[j + k] = temp;

			}
		}

	} while (k != 1);
	free(copy);
}