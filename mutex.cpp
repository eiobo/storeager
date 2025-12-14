#include <array>
#include <thread>
#include <iostream>

void inc(int &res)
{
    for (int i = 0; i < 1000000; i++)
        res++;
}

int main(void)
{
    int counter = 0;
    std::thread th1(inc, std::ref(counter));
    std::thread th2(inc, std::ref(counter));

    th1.join();
    th2.join();

    std::cout << "counter=" << counter << "\n";
}

// #define _LOCK_GUARD
// // #define _PURE_MUTEX
// #include <array>
// #include <thread>
// #include <iostream>
// #include <mutex>

// #ifdef _PURE_MUTEX
// class Counter{
// public:
//     void inc()
//     {
//         counter_mutex.lock();
//         m_count++;
//         counter_mutex.unlock();
//     }
//     int get() {
//         int temp;
//         counter_mutex.lock();
//         temp = m_count;
//         counter_mutex.unlock();
//         return temp;
//     }
// private:
//     std::mutex counter_mutex;
//     int m_count = 0;
// };
// #endif


// #ifdef _LOCK_GUARD
// class Counter{
// public:
//     void inc(){
//         std::lock_guard<std::mutex> lock(counter_mutex);
//         m_count++;
//     }

//     int get(){
//         std::lock_guard<std::mutex> lock(counter_mutex);
//         return m_count;
//     }
// private:
//     std::mutex counter_mutex;
//     int m_count = 0;
// };
// #endif


// int main(void) {
//     Counter counter; 
//     auto increase = [](Counter& counter) { for (int i = 0; i < 1000000; i++) counter.inc(); };          // 定义的任务
//     std::thread th1(increase, std::ref(counter));                                                       // 第二个参数是向线程传递的参数
//     std::thread th2(increase, std::ref(counter));

//     // 注意： th1和th2谁先完成是不确定的，所以每个th1和th2都要join， main函数会阻塞，直至所有子线程执行完毕
//     th1.join();             // 阻塞th1线程，直至执行完1000000运算
//     th2.join();             // 阻塞th2线程，直至执行完1000000运算

//     std::cout << "counter=" << counter.get() << "\n";               // 运行到这就能确保th1和th2都执行完毕
// }
