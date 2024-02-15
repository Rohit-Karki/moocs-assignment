#include <iostream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <string>

using namespace std;
// g_mutex is the mutex to synchronize the access of shared variable g_data
std::mutex g_mutex;
int n = 0;
bool g_ready = false;
int g_data = 0;

void consumeData(int data) { std::cout << "Consumer got: " << data << "\n"; }
int produceData()
{
    std::cout << "Producer produced: " << n++ << "\n";
    return randomNumber;
}

// consumer thread function
void consumer()
{
    while (true)
    {
        while (!g_ready)
        {
            // Sleep for 1 sec to wait
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::unique_lock<std::mutex> ul(g_mutex);
        consumeData(g_data);
        g_ready = false;
    }
}

// Producer thread function
void producer()
{
    while (true)
    {
        std::unique_lock<std::mutex> ul(g_mutex);

        g_data = produceData();
        g_ready = true;
        ul.unlock();
        while (g_ready)
        {
            // sleep for 1 sec to let thread wait
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}
void consumerThread() { consumer(); }

void producerThread() { producer(); }

int main(int argc, char *argv[])
{
    std::thread t1(consumerThread);
    std::thread t2(producerThread);
    t1.join();
    t2.join();
    return 0;
}