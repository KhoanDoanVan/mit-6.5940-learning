#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

int counter = 0;
mutex mtx;

void increment_task(int times) {
    for (int i = 0; i < times; ++i) {
        lock_guard<mutex> lock(mtx);
        counter++;
    }
}

int main() {
    vector<thread> threads;
    int num_threads = 4;
    int times = 100000;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_task, times);
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "counter = " << counter << '\n';
    return 0;
}