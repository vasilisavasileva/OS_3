#include<iostream>
#include<vector>
#include<Windows.h>
#include"EvenOddSort.h"
#include<limits>

int main() {

	std::cout << "Write size of vector: ";
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::cout << "Write count of threads: ";
	int l;
	std::cin >> l;
	int oldSize = a.size();
	while ((double)((int)log2(a.size())) != log2(a.size())) {
		a.push_back(INT_MAX);
	}
	OddEvenMergeSort(a, l, 0, n - 1);
	for (int i = 0; i < a.size() - oldSize;++i)
		a.pop_back();
	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << ' ';
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}