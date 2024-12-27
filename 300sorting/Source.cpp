#include <iostream>
#include <vector>
#include "MinHeap.cpp"

using namespace std;

void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void insertionSort(vector<int>& vec) {
    for (int i = 1; i < vec.size(); i++) {
        int current = vec[i];
        for (int j = i - 1; (j >= 0) && (vec[j] > current);j--) {
            swap(vec[j], vec[j + 1]);
        }
    }
}

vector<int> heapSort(vector<int> vec) {
    vector<int> sortedVec;
    MinHeap heap(vec);

    while (heap.size() > 1) {
        sortedVec.push_back(heap.deleteMin());
    }
    return sortedVec;
}

void merge(vector<int> &vec, int l, int mid, int h) {
    vector<int> merged;

    int i = l;
    int j = mid+1;


    while (i <= mid && j <= h) {
        if (vec[i] <= vec[j]) {
            merged.push_back(vec[i]);
            i++;
        }
        else {
            merged.push_back(vec[j]);
            j++;
        }
    }

    // Copy remaining elements from the first subarray
    while (i <= mid) {
        merged.push_back(vec[i]);
        i++;
    }

    // Copy remaining elements from the second subarray
    while (j <= h) {
        merged.push_back(vec[j]);
        j++;
    }

    for (int k = 0; k < merged.size(); k++) {
        vec[l + k] = merged[k];
    }

}

void mergeSort(vector<int> &vec,int l, int h) {

    if (l < h) {
        int mid = (l +h )/ 2;
        mergeSort(vec, l, mid);
        mergeSort(vec, mid + 1, h);
        merge(vec, l, mid, h);
    }
}

int main() {
    
	vector<int> numbers = { 42, 17, 8, 23, 60, 5, 12, 90, 1, 33 };

	// insertionSort(numbers);
    // numbers = heapSort(numbers);

    mergeSort(numbers,0,numbers.size()-1);

    printVector(numbers);
}