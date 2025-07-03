#include <iostream>
#include <memory>
#include <thread>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <mutex>
using namespace std;

int thread_count;

mutex m;

double sum = 0.0;

void worker(int my_rank, int n) {
    double my_sum = 0;
    int my_n = n / thread_count;
    int my_first_i = my_rank * my_n;
    int my_end_i = (my_rank + 1) *my_n - 1;
    double factor = my_first_i % 2 == 0 ? 1.0 : -1.0;

    for(int i = my_first_i; i < my_end_i; ++i, factor *= -1) {
        my_sum += factor / (2*i + 1);
    }
    m.lock();
    sum+= my_sum;
    m.unlock();
}

int main() {

    thread_count = thread::hardware_concurrency();
    cout << thread_count << endl;
    vector<thread> thread_handles;

    for(int i = 0; i < thread_count; ++i)
        thread_handles.push_back(thread(worker, i, INT64_MAX));

    for(int i = 0; i < thread_count; ++i)
        thread_handles[i].join();

    cout << setprecision(10);
    cout << 4 * sum << endl;

}

//SMART POINTERS
//unique_ptr - только один указатель на объект.
//shared_ptr - несколько указателей могут указывать на одну и ту же область памяти.
//weak_ptr - слабый указатель, выставляет иерархию.

//MULTITHREADS
//thread::hardware_concurrency


//--------------------------------------------------------------------------
// #include <iostream>
// #include <memory>
// #include <thread>
// #include <cstdio>
// #include <vector>
// using namespace std;

// int thread_count;

// void worker(int my_rank) {
//     printf("Hello from thread %d from %d\n", my_rank, thread_count);
// }

// int main() {

//     thread_count = thread::hardware_concurrency();
//     cout << thread_count << endl;
//     vector<thread> thread_handles;

//     for(int i = 0; i < thread_count; ++i)
//         thread_handles.push_back(thread(worker, i));

//     for(int i = 0; i < thread_count; ++i)
//         thread_handles[i].join();

// }