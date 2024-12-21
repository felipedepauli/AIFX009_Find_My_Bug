#include "Server.hpp"
#include "../Comm.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <memory>

// ThreadPool implementation
class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount) : stop(false) {
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;

                    // Critical section to access the task queue
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        condition.wait(lock, [this]() { return stop || !tasks.empty(); });

                        if (stop && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    // Execute the task
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        // Stop all threads
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();

        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

    void addTask(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            tasks.push(std::move(task));
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};


// Main server logic
int main() {
    try {
        Comm comm;

        // Create the thread pool with 10 threads
        ThreadPool poolThreads(10);

        while (true) {
            // Accepts the connection and returns the socket
            auto socket = comm.startListening(8080);

            // Create a new processing object
            auto processing = std::make_shared<Processing>();

            // Bind the socket to the processing
            auto task = comm.bind(std::move(socket), processing);

            // Add the task to the thread pool
            poolThreads.addTask(std::move(task));
        }

    } catch (std::exception& e) {
        std::cerr << "[Server] Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
