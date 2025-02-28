#include<iostream>
#include <vector>

struct node {
    unsigned long long time;
    int id;
};

class Heap {
private:
    std::vector<node> array;

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = array.size();

        if(left < size) {
            if(array[left].time < array[smallest].time) {
                smallest = left;
            } else if (array[left].time == array[smallest].time) {
                if(array[left].id < array[smallest].id) {
                    smallest = left;
                }
            }
        }

        if(right < size)
            if(array[right].time < array[smallest].time) {
                smallest = right;
            } else if(array[right].time == array[smallest].time) {
                if(array[right].id < array[smallest].id) {
                    smallest = right;
                }
            }

        if(smallest != i) {
            node temp = array[smallest];
            array[smallest] = array[i];
            array[i] = temp;

            heapify(smallest);
        }
    }

    void fixUp(int i) {
        while (i != 0) {
            if((array[(i - 1) / 2].time > array[i].time) or 
            (array[(i - 1) / 2].time == array[i].time and 
            array[(i - 1) / 2].id > array[i].id)) {
                node temp = array[(i - 1) / 2];
                array[(i - 1) / 2] = array[i];
                array[i] = temp;

                i = (i - 1) / 2;
            } else { break; }
        }
    }



public:
    Heap(int n) {
        for(int i = 0; i < n; i++) {
            array.push_back({0, i});
        }
    }

    void insert(unsigned long long time, int id) {
        node current = {time, id};
        array.push_back(current);
        fixUp(array.size() - 1);
    }

    node extractMin() {
        if(array.size() <= 0) {return {0, -1};}

        if(array.size() == 1) {
            node root = array[0];
            array.pop_back();
            return root;
        }

        node root = array[0];
        array[0] = array.back();
        array.pop_back();
        heapify(0);

        return root;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Heap heap(n);

    for(int i = 0; i < m; i++) {
        unsigned long long current;
        std::cin >> current;

        node temp = heap.extractMin();
        std::cout << temp.id << " " << temp.time << std::endl;

        heap.insert(temp.time + current, temp.id);
    }
}