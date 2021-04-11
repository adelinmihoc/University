#pragma once
#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	SortedMultiMap& map;
	SMMIterator(SortedMultiMap& map);

    std::vector<TElem> sorted_vector;
    int capacity;
    int current;

    bool relation(TElem a, TElem b) {
        return map.relation(a.first, b.first);
    }

    void mergeSort(std::vector<TElem>& arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l)/ 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m+1, r);
            merge(arr, l, m, r);
        }
    }

    void merge(std::vector<TElem>& arr, int l, int m, int r) {
        int i, j ,k;
        int n1 = m - l + 1;
        int n2 = r - m;
        TElem L[n1], R[n2];
        for (i = 0; i < n1; i++) {
            L[i] = arr[l + i];
        }
        for (j = 0; j < n2; j++) {
            R[j] = arr[m + 1 + j];
        }
        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (this->relation(L[i], R[j])) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
    TElem remove();
};

