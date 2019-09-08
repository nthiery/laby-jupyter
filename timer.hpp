#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

class Timer
{
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    std::function<void()> tick;
    int fps;
    bool _running = false;
    std::chrono::time_point<std::chrono::system_clock> last_tick;
    std::thread thread;

    public:
    Timer(std::function<void()> _tick, int _fps) : tick(_tick), fps(_fps) {
    }
    ~Timer() {
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (_running) {
                _running = false;
                m_condVar.notify_one();
            }
        }
        if (thread.joinable()) {
            thread.join();
        }
    }

    void notify()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_condVar.notify_one();
    }

    void set_fps(int _fps) {
        std::lock_guard<std::mutex> guard(m_mutex);
        fps = _fps;
        m_condVar.notify_one();
    }

    void run() {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (_running)
            return;
        _running = true;
        thread = std::thread(&Timer::thread_code, this);
    }

    bool running() {
        return _running;
    }

    void thread_code()
    {
        last_tick = std::chrono::system_clock::now();
        while (true) {
            while (true) { // Wait until next tick time
                if (not _running)
                    return;
                std::unique_lock<std::mutex> mlock(m_mutex);
                if (fps == 0) {
                    m_condVar.wait(mlock);
                } else {
                    auto next_tick = last_tick + 1000ms / fps;
                    if ( std::chrono::system_clock::now() >= next_tick )
                        break;
                    m_condVar.wait_until(mlock, next_tick);
                }
            }
            tick();
            last_tick = std::chrono::system_clock::now();
        }
    }
};
