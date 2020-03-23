#pragma once
#include<iostream>
#include<vector>
#include<Windows.h>
#include<malloc.h>

void EvenOddSort(std::vector<int>& a, int& n, unsigned int l, unsigned int r);

typedef struct param {
	std::vector<int>& a;
	int& n;
	unsigned int l;
	unsigned int r;
};

void compexch(int& a, int& b)
{
	if (b < a)
		std::swap(a, b);
}


void shuffle(std::vector<int>& a, unsigned int l, unsigned int r)
{
	auto half = (unsigned int)(l + r) / 2;
	std::vector<int> tmp(a.size());
	unsigned int i, j;
	for (i = l, j = 0; i <= r; i += 2, j++)
	{
		tmp[i] = a[l + j];
		tmp[i + 1] = a[half + j + 1];
	}
	for (auto i = 0; i < tmp.size(); i++)
		a[i] = tmp[i];
}


void unshuffle(std::vector<int>& a, unsigned int l, unsigned int r)
{
	auto half = (unsigned int)(l + r) / 2;
	std::vector<int> tmp(a.size());
	unsigned int i, j;
	for (i = l, j = 0; i <= r; i += 2, j++)
	{
		tmp[l + j] = a[i];
		tmp[half + j + 1] = a[i + 1];
	}
	for (auto i = 0; i < tmp.size(); i++)
		a[i] = tmp[i];
}

DWORD WINAPI EvenOddSortThread(LPVOID Parametr) {
	param* P = (param*)Parametr;
	unsigned int& r = P->r;
	unsigned int& l = P->l;
	int& n = P->n;
	std::vector<int>& a = P->a;
	if (r == l + 1) compexch(a[l], a[r]); //мы дошли до подмассива размера 2 - теперь просто сравним элементы
	if (r < l + 2) return 0; //дошли до подмассива размера 1 - выходим, такой подмассив априори отсортирован
	unshuffle(a, l, r); //делим подмассив на две части
	auto half = (unsigned int)(l + r) / 2;//делим подмассив на две части
	HANDLE Thread1 = INVALID_HANDLE_VALUE;
	HANDLE Thread2 = INVALID_HANDLE_VALUE;
	param* P1 = nullptr;
	param* P2 = nullptr;
	if (n != 0) {
		--n;
		P1 = (param*)malloc(sizeof(param));
		P1->a = a;
		P1->n = n;
		P1->r = half;
		P1->l = l;
		Thread1 = CreateThread(NULL, 0, EvenOddSortThread, P1, 0, NULL);
	}
	else {
		EvenOddSort(a, n, l, half);
	}
	if (n != 0) {
		--n;
		P2 = (param*)malloc(sizeof(param));
		P2->a = a;
		P2->n = n;
		P2->r = half + 1;
		P2->l = l;
		Thread2 = CreateThread(NULL, 0, EvenOddSortThread, P2, 0, NULL);
	}
	else {
		EvenOddSort(a, n, half + 1, r);
	}
	if (Thread1 != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(Thread1, INFINITE);
		free(P1);
	}
	if (Thread2 != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(Thread2, INFINITE);
		free(P2);
	}
	shuffle(a, l, r); //сливаем части
	for (auto i = l + 1; i < r; i += 2)
		compexch(a[i], a[i + 1]);
	auto halfSize = (r - l + 1) / 2 - 1;       //*
	for (int i = l + 1; i + halfSize < r; i++) //*
		compexch(a[i], a[i + halfSize]);

}

void EvenOddSort(std::vector<int> &a, int &n, unsigned int l, unsigned int r) {
	if (r == l + 1) compexch(a[l], a[r]); //мы дошли до подмассива размера 2 - теперь просто сравним элементы
	if (r < l + 2) return; //дошли до подмассива размера 1 - выходим, такой подмассив априори отсортирован
	unshuffle(a, l, r); 
	auto half = (unsigned int)(l + r) / 2;//делим подмассив на две части
	HANDLE Thread1 = INVALID_HANDLE_VALUE;
	HANDLE Thread2 = INVALID_HANDLE_VALUE;
	param* P1 = nullptr;
	param* P2 = nullptr;
	if (n != 0) {
		--n;
		P1 = (param*)malloc(sizeof(param));
		P1->a = a;
		P1->n = n;
		P1->r = half;
		P1->l = l;
		Thread1 = CreateThread(NULL, 0, EvenOddSortThread, P1, 0, NULL);
	}
	else {
		EvenOddSort(a, n, l, half);
	}
	if (n != 0) {
		--n;
		P2 = (param*)malloc(sizeof(param));
		P2->a = a;
		P2->n = n;
		P2->r = half + 1;
		P2->l = l;
		Thread2 = CreateThread(NULL, 0, EvenOddSortThread, P2, 0, NULL);
	}
	else {
		EvenOddSort(a, n, half + 1, r);
	}
	if (Thread1 != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(Thread1, INFINITE);
		free(P1);
	}
	if (Thread2 != INVALID_HANDLE_VALUE) {
		WaitForSingleObject(Thread2, INFINITE);
		free(P2);
	}
	shuffle(a, l, r); //сливаем части
	for (auto i = l + 1; i < r; i += 2)
		compexch(a[i], a[i + 1]);
	auto halfSize = (r - l + 1) / 2 - 1;       //*
	for (int i = l + 1; i + halfSize < r; i++) //*
		compexch(a[i], a[i + halfSize]);

}