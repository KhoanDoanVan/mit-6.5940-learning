#include <iostream>
#include <thread>
using namespace std;

void task(int id) {
    for (int i = 0; i < 5; ++i) {
        cout << "Thread " << id << " -> " << i << '\n';
    }
}

int main() {
    thread t1(task, 1);
    thread t2(task, 2);

    t1.join();
    t2.join();

    cout << "Done\n";
    return 0;
}