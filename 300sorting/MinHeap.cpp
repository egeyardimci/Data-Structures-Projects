#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> heap;

    void percUpHeap(int idx) {
        int parrentIdx = idx / 2;
        if (parrentIdx <= 0) {
            return;
        }
        if (heap[parrentIdx] > heap[idx]) {
            swap(heap[parrentIdx], heap[idx]);
        }
        percUpHeap(parrentIdx);
    }

    void percDownHeap(int idx) {
        int child1 = idx * 2;
        int child2 = (idx * 2) + 1;
        if (child2 >= heap.size()) {
            return;
        }
        if (heap[child1] < heap[child2]) {
            if (heap[child1] < heap[idx]) {
                swap(heap[child1], heap[idx]);
                percDownHeap(child1);
            }
        }
        else {
            if (heap[child2] < heap[idx]) {
                swap(heap[child2], heap[idx]);
                percDownHeap(child2);
            }
        }

    }


public:
    MinHeap(vector<int> vec) {
        heap.push_back(-1);

        for (int i : vec) {
            insert(i);
        }
    };

    int deleteMin() {
        int result = heap[1];
        heap[1] = heap[heap.size() - 1];
        heap.pop_back();

        percDownHeap(1);
        return result;
    }

    void insert(int i) {
        heap.push_back(i);
        percUpHeap(heap.size() - 1);
    }

    int size() {
        return heap.size();
    }

};
