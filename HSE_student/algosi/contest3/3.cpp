#include <iostream>
#include <vector>

struct node {
    int a;
    int b;
};

class Heap {
private:
    std::vector<unsigned long long int> array;
    std::vector<node> history;

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = array.size();

        if (left < size && array[left] < array[smallest]) {
            smallest = left;
        }

        if (right < size && array[right] < array[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            unsigned long long int temp = array[smallest];
            array[smallest] = array[i];
            array[i] = temp;
            node step = {i, smallest};
            history.push_back(step);
            heapify(smallest);
        }
    }

public:
    Heap(const std::vector<unsigned long long int>& input) : array(input) {
        int n = array.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(i);
        }
    }

    const std::vector<node>& History() {
        return history;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<unsigned long long int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    Heap heap(array);
    const std::vector<node>& history = heap.History();

    std::cout << history.size() << std::endl;
    for (const auto& step : history) {
        std::cout << step.a << " " << step.b << std::endl;
    }

    return 0;
}