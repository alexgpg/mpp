#include <atomic>
#include <vector>
#include <thread>
#include <iostream>

namespace mpp {

class spinlock {
  spinlock(const spinlock&) = delete;
  spinlock(spinlock&&) = delete;
  spinlock& operator=(const spinlock&) = delete;
  spinlock& operator=(spinlock&&) = delete;
public:
  spinlock() = default;

  void lock() {
    while(locked_.test_and_set(std::memory_order_acquire)); // Spin
  }

  void unlock() {
    locked_.clear(std::memory_order_release);
  }
private:
  std::atomic_flag locked_ = ATOMIC_FLAG_INIT;
};

}

int main() {
  mpp::spinlock lock;

  // Start many thread.
  const unsigned n = std::thread::hardware_concurrency();
  std::vector<std::thread> workers;

  for(unsigned i = 0; i < n; i++) {
    workers.push_back(std::thread([i, &lock](){
      for(size_t i = 0; i < 100; i++) {
        {
          // Automaticaly call unlock in destructor.
          std::lock_guard<mpp::spinlock> lock_guard(lock);
          std::cout << "Hello from " << i << '\n';
        }
      }
    }));
  }

  std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
    t.join();
  });

  return 0;
}
