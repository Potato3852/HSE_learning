#include<initializer_list>
#include<algorithm>
#include<cstring>

class Vector{
public:
    int getSize() {return size;}
    int getCapacity() { return capacity;}
    void print() {
        for(int i = 0; i < size; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }
    Vector() = default;
    Vector(int n, int x) : Vector(n) {
        memset(arr, x, n*sizeof(int));
    }
    Vector(std::initializer_list<int> list) : Vector(list.size()) {
        std::copy(list.begin(), list.end(), arr);
    }
    Vector(const Vector& another) : arr(new int[another.size]), capacity(another.capacity), size(another.size) {
        memcpy(arr, another.arr, size*sizeof(int));
    }
    auto operator=(Vector v) {
        Swap(v);
        return *this;
    }
    void Swap(Vector& v) {
        std::swap(arr, v.arr);
        std::swap(capacity, v.capacity);
        std::swap(size, v.size);
    }
     ~Vector(){delete[] arr;}
private:
    Vector(int n) : arr(new int[n]), size(n), capacity(n) {}
    int* arr = nullptr;
    int capacity = 0;
    int size = 0;
};