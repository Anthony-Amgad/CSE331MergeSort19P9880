#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#define LENGTH 10000
using namespace std;

void createRandFile() {
	ofstream mfile("unsortedFile.txt");
	srand(time(0));

	for (int i = 0; i < LENGTH; i++) {
		mfile << ((rand() % LENGTH) + 1) << endl;
	}
}

void readFile(int arr[], int l) {
	ifstream mfile("unsortedFile.txt");
	for (int i = 0; i < l; i++) {
		mfile >> arr[i];
	}
}

void createSortedFile(int arr[]) {
	ofstream mfile("sortedFile.txt");

	for (int i = 0; i < LENGTH; i++) {
		mfile << arr[i] << endl;
	}
}

int merge(int arr[], int s, int m, int l) {
	int step = 5;
	int* firstarr = new int[m - s + 1];
	int* secondarr = new int[l - m];
	for (int i = 0; i < m - s + 1; i++) {
		firstarr[i] = arr[s + i];
		step++;
	}
	for (int i = 0; i < l - m; i++) {
		secondarr[i] = arr[m + i +1];
		step++;
	}
	int i = 0, j = 0, k = s;

	while (i < m - s + 1 && j < l - m) {
		if (firstarr[i] < secondarr[j]) {
			arr[k] = firstarr[i];
			i++;
			step += 2;
		}
		else {
			arr[k] = secondarr[j];
			j++;
			step += 2;
		}
		k++;
		step++;
	}

	while (i < m - s + 1) {
		arr[k] = firstarr[i];
		i++; k++;
		step += 3;
	}

	while (j < l - m) {
		arr[k] = secondarr[j];
		j++; k++;
		step += 3;
	}

	delete[] firstarr;
	delete[] secondarr;
	return step;
}

int mergeSort(int arr[], int s, int l) {
	int step = 1;
	if (s >= l)
		return step;
	int mid = (s + l) / 2;
	step += mergeSort(arr, s, mid);
	step += mergeSort(arr, mid + 1, l);
	step += merge(arr, s, mid, l);
	return step;
}

int main() {
	int arr[LENGTH];
	createRandFile();
	readFile(arr, LENGTH);

	ofstream sFile("clockFile.txt");
	int x[LENGTH];

	for (int i = 10; i <= 10000; i *= 10) {
		for (int j = 0; j < i; j++) {
			x[j] = arr[j];
		}
		clock_t time = clock();
		mergeSort(x, 0, i - 1);
		sFile << i << ',' << (float)(clock() - time) / CLOCKS_PER_SEC << endl;
	}

	ofstream bFile("stepFile.txt");
	int y[LENGTH];

	for (int i = 10; i < 10000; i += 50) {
		for (int j = 0; j < i; j++) {
			y[j] = arr[j];
		}
		bFile << i << ',' << mergeSort(y, 0, i - 1) << endl;
	}

	bFile << 10000 << ',' << mergeSort(arr, 0, LENGTH - 1) << endl;
	
	createSortedFile(arr);
	system("pause");
	return 0;
}