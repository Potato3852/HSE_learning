#include<iostream>
#include <vector>
#include <string>

class Heap {
private:
    int size;
    std::vector<unsigned long long int> array;

    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = array.size();

        if(left < size and array[left] > array[largest]) {
            largest = left;
        }

        if(right < size and array[right] > array[largest]) {
            largest = right;
        }

        if(largest != i) {
            unsigned long long int temp = array[largest];
            array[largest] = array[i];
            array[i] = temp;
            heapify(largest);
        }
    }

public:
    void insert(unsigned long long int key) {
        array.push_back(key);
        int i = array.size() - 1;
        
        while(i != 0 and array[(i - 1) / 2] < array[i]) {
            unsigned long long int temp = array[(i - 1) / 2];
            array[(i - 1) / 2] = array[i];
            array[i] = temp;
            i = (i - 1) / 2;
        }
    }

    void extractMax() {
        if(array.size() <= 0) {return;}

        if(array.size() == 1) {
            unsigned long long int root = array[0];
            array.pop_back();
            std::cout << root << std::endl;
            return;
        }

        unsigned long long int root = array[0];
        array[0] = array.back();
        array.pop_back();
        heapify(0);

        std::cout << root << std::endl;
    }

};

int main() {
    int n;
    unsigned long long int x;
    std::cin >> n;
    Heap heap;

    std::string command;
    for(int i = 0; i < n; i++) {
        std::cin >> command;
        if(command == "Insert") {
            std::cin >> x;
            heap.insert(x);
        }
        if(command == "ExtractMax") {
            heap.extractMax();
        }
    }
}