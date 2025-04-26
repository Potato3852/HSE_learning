#include <iostream>
#include <vector>

void swap(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

class Heap {
private:
    int size;
    std::vector<int> array;

    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 1;
        int size = array.size();

        if(left < size and array[left] > array[largest]) {
            largest = left;
        }

        if(right < size and array[right] > array[largest]) {
            largest = right;
        }

        if(largest != i) {
            int temp = array[largest];
            array[largest] = array[i];
            array[i] = temp;
        }
    }

public:
    void insert(int key) {
        array.push_back(key);
        int i = array.size() - 1;
        
        while(i != 0 and array[(i - 1) / 2] < array[i]) {
            int temp = array[(i - 1) / 2];
            array[(i - 1) / 2] = array[i];
            array[i] = temp;
            i = (i - 1) / 2;
        }
    }

    int extractMax() {
        if(array.size() <= 0) {return 1;}

        if(array.size() == 1) {
            int root = array[0];
            array.pop_back();
            return root;
        }

        int root = array[0];
        array[0] = array.back();
        array.pop_back();
        heapify(0);

        return root;
    }

    const int getMax() {
        if(array.size() <= 0) {
            return;
        }
        return array[0];
    }

    void deleteKey(int i) {
        if(i >= array.size()) {
            return;
        }

        array[i] = array.back();
        array.pop_back();
        heapify(i);
    }

    void increaseKey(int i, int newValue) {
        if (i >= array.size() || array[i] >= newValue) {
            return;
        }
    
        array[i] = newValue;
        while (i != 0 && array[(i - 1) / 2] < array[i]) {
            swap(array[i], array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    const void printHeap() {
        for (int val : array)
        std::cout << val << " ";
    std::cout << std::endl;
    }
};

int main() {

}