//
// Created by andrew on 2021/4/3.
//
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

using namespace std;


bool more_data_to_prepare()
{
    return false;
}

struct data_chunk
{};

data_chunk prepare_data()
{
    return {};
}

void process(data_chunk&)
{}

bool is_last_chunk(data_chunk&)
{
    return true;
}

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;


void data_preparation_thread()
{
    while(more_data_to_prepare())
    {
        data_chunk const data=prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
}

void data_processing_thread()
{
    while(true)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[]{return !data_queue.empty();});
        data_chunk data=data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
        if(is_last_chunk(data))
            break;
    }
}

int main(int argc, char*argv[]) {
    thread t1(data_preparation_thread);
    thread t2(data_processing_thread);

    t1.join();
    t2.join();
    return 0;
}
