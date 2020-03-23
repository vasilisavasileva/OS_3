#include<iostream>
#include<vector>
#include"EvenOddSort.h"
#include<stdlib.h>
#include<Windows.h>

int main() {
	int n, l;
	std::cout << "Write size for vector" << std::endl;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	std::cout << "Write the number of threads" << std::endl;
	std::cin >> l;
	EvenOddSort(a, l, 0, n - 1);
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << '\t';
	}
	return 0;
}