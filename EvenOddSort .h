#pragma once
#include<iostream>
#include<vector> 
#include<Windows.h>
#include<malloc.h>
//*
struct Param {
    std::vector<int>& a;
    int& n;
    int l;
    int r;
    Param(std::vector<int>& _a, int& _n, int _l, int _r) : a(_a), n(_n), l(_l), r(_r) {}
};
void OddEvenMergeSort(std::vector<int>& a, int& n, int l, int r);
void shuffle(std::vector<int>& a, int l, int r)
{
    int half = (l + r) / 2;
    std::vector<int> tmp(a.size());
    int i = l, j = half + 1;
    int k = l;
    while (i <= half && j <= r) {
        if (a[i] < a[j]) {
            tmp[k] = a[i];
            ++i;
            ++k;
        }
        else {
            tmp[k] = a[j];
            ++j;
            ++k;
        }
    }
    for (int n = i; n <= half; ++n) {
        tmp[k] = a[n];
        ++k;
    }

    for (int n = j; n <= r; ++n) {
        tmp[k] = a[n];
        ++k;
    }
    for (int i = l; i <= r; ++i) {
        a[i] = tmp[i];
    }
}


void unshuffle(std::vector<int>& a, int l, int r)
{
    int half = (l + r) / 2;
    std::vector<int> tmp(a.size());
    int i, j;
    for (i = l, j = 0; i <= r; i += 2, j++)
    {
        tmp[l + j] = a[i];
        tmp[half + j + 1] = a[i + 1];
    }
    for (int i = l; i <=r; i++)
        a[i] = tmp[i];
}

void compexch(int& a, int& b)
{
    if (b < a)
        std::swap(a, b);
}
DWORD WINAPI OddEvenMergeSortThread(LPVOID Parametr) {
    Param* P = (Param*)Parametr;
    int& r = P->r;
    int& l = P->l;
    int& n = P->n;
    std::vector<int>& a = P->a;
    if (r == l + 1)
        compexch(a[l], a[r]);
    if (r < l + 2)
        return 0;
    unshuffle(a, l, r);
    int half = (l + r) / 2;


    HANDLE Thread1 = INVALID_HANDLE_VALUE;
    HANDLE Thread2 = INVALID_HANDLE_VALUE;
    Param* P1 = nullptr;
    Param* P2 = nullptr;
    if (n != 0) {
        --n;
        P1 = new Param(a, n, l, half);
        Thread1 = CreateThread(NULL, 0, OddEvenMergeSortThread, P1, 0, NULL);
    }
    else {
        OddEvenMergeSort(a, n, l, half);
    }
    if (n != 0) {
        --n;
        P2 = new Param(a, n, half+1 , r);
        Thread2 = CreateThread(NULL, 0, OddEvenMergeSortThread, P2, 0, NULL);
    }
    else {
        OddEvenMergeSort(a, n, half + 1, r);
    }

    if (Thread1 != INVALID_HANDLE_VALUE) {
        WaitForSingleObject(Thread1, INFINITE);
        free(P1);
    }
    if (Thread2 != INVALID_HANDLE_VALUE) {
        WaitForSingleObject(Thread2, INFINITE);
        free(P2);
    }
    shuffle(a, l, r);
    for (auto i = l + 1; i < r; i += 2)
        compexch(a[i], a[i + 1]);
    int halfSize = (r - l + 1) / 2 - 1;
    for (int i = l + 1; i + halfSize < r; i++)
        compexch(a[i], a[i + halfSize]);
}

void OddEvenMergeSort(std::vector<int>& a, int& n, int l, int r) {
    if (r == l + 1)
        compexch(a[l], a[r]);
    if (r < l + 2)
        return; 
    unshuffle(a, l, r); 
    int half = (l + r) / 2;

    HANDLE Thread1 = INVALID_HANDLE_VALUE;
    HANDLE Thread2 = INVALID_HANDLE_VALUE;
    Param* P1 = nullptr;
    Param* P2 = nullptr;
    if (n != 0) {
        --n;
        P1 = new Param(a, n, l, half);
        Thread1 = CreateThread(NULL, 0, OddEvenMergeSortThread, P1, 0, NULL);
    }
    else {
        OddEvenMergeSort(a, n, l, half);
    }
    if (n != 0) {
        --n;
        P2 = new Param(a, n, half + 1, r);
        Thread2 = CreateThread(NULL, 0, OddEvenMergeSortThread, P2, 0, NULL);
    }
    else {
        OddEvenMergeSort(a, n, half + 1, r);
    }

    if (Thread1 != INVALID_HANDLE_VALUE) {
        WaitForSingleObject(Thread1, INFINITE);
        free(P1);
    }
    if (Thread2 != INVALID_HANDLE_VALUE) {
        WaitForSingleObject(Thread2, INFINITE);
        free(P2);
    }
    shuffle(a, l, r);
    for (int i = l + 1; i < r; i += 2)
        compexch(a[i], a[i + 1]);
    int halfSize = (r - l + 1) / 2 - 1;
    for (int i = l + 1; i + halfSize < r; i++)
        compexch(a[i], a[i + halfSize]);
}