#pragma once

#include <list>
#include <mutex>

// Simple Thread-safe Queue
template<typename T>
class ThreadedQueue {
public:
    ThreadedQueue() = default;
    ~ThreadedQueue()
    {
        for (T thing: this->things) {
            delete thing;
        }
    }

    void push(T thing)
    {
        lock_guard(this->mutex);
        this->things.push_back(thing);
    }

    T pop() {
        lock_guard(this->mutex);
        T thing;
        if (this->things.size() > 0) {
            thing = this->things.front();
            this->things.pop_front();
        }
        else {
            thing = nullptr;
        }
        return thing;
    }

private:
    typedef std::lock_guard<std::mutex> lock_guard;
    std::mutex mutex;
    std::list<T> things;
};