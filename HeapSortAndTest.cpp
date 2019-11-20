#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
using namespace std;

void checkOut(vector<int> vector) {
	for (int i = 0; i < vector.size(); i++) {
		cout << vector.at(i) << endl;
	}
}
void recoverHeap(vector<int>* heap, int index, int length) {
	int maxIndex = index;//maximum
	int lIndex = 2 * index + 1;//left
	int rIndex = 2 * index + 2;//right

	if (lIndex < length && (*heap).at(lIndex) > (*heap).at(maxIndex))
		maxIndex = lIndex;
	if (rIndex < length && (*heap).at(rIndex) > (*heap).at(maxIndex))
		maxIndex = rIndex;

	if (maxIndex != index) {

		swap((*heap).at(maxIndex), (*heap).at(index));
		recoverHeap((heap), maxIndex, length);
	}
}

void heapSort(vector<int>* heap, int length) {

	for (int i = length/2 - 1;i >= 0; i--) {
		recoverHeap(heap, i, length); // Recovering
	}
	for (int i = length - 1; i >= 0; i--) {
		swap((*heap).at(0), (*heap).at(i));
		recoverHeap(heap, 0, i);
	}
}

void TheapSort(vector<int>* heap, int length) {
	cout << "Recovering... \n";
	int count = length / 2 - 1;
	for (int i = 0; i < count; i++)
		cout << "=";
	cout << "\n";
	clock_t t1 = clock();
	for (int i = length / 2 - 1;i >= 0; i--) {
		if ((100 - (i / count)*100) % (count) == 0)
			cout << "=";
		recoverHeap(heap, i, length);
	}
	clock_t t2 = clock();
	printf("\n Time : %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
	cout << "\n End of Recovering. Sort... \n";
	count = (length - 1)/10;
	for (int i = 0; i < 10; i++)
		cout << "=";
	cout << "\n";
	t1 = clock();
	for (int i = length - 1; i >= 0; i--) {
		if ((100 - (i / count)) % (count) == 0)
			cout << "=";
		swap((*heap).at(0), (*heap).at(i));
		recoverHeap(heap, 0, i);
	}
	t2 = clock();
	printf("\n Time : %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}

int main(int len, char* args[])
{
	int silent = 0;
	int testermod = 0;
	int fileoutput = 0;
	int notRandom = 0;
	string filename = "";

	if (len == 1) {
		silent = 1;
	}
	for (int i = 1; i < len; i++) {
		if (*args[i] == 's')
			silent = 1;
		//else if (*args[i] == 't')
		//	testermod = 1;
		else if (*args[i] == 'n')
			notRandom = 1;
		else if (*args[i] == 'f' && len != i + 1) {
			fileoutput = 1;
			filename = args[i + 1];
		}
	}
	int n = 0;
	vector<int> mass;
	srand(time(0));
	setlocale(LC_ALL, "Russian");
    cout << "Количество элементов в массиве : ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		if (notRandom) {
			int n = 0;
			cin >> n;
			mass.push_back(n);
		}else
			mass.push_back(rand());
	}
	if (testermod) {
		clock_t t1 = clock();
		TheapSort(&mass, mass.size());
		clock_t t2 = clock();
		printf("Время выполнения : %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
	}
	else {
		clock_t t1 = clock();
		heapSort(&mass, mass.size());
		clock_t t2 = clock();
		printf("Время выполнения : %f\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
	}

	if (silent == 0) {
		cout << "Результат работы " <<endl;
		checkOut(mass);
	}
	if (fileoutput) {
		ofstream file;
		file.open(filename);
		for (int i = 0; i < mass.size(); i++)
			file << mass.at(i) << endl;
		file.close();
	}
	system("pause");
	return 0;
}
