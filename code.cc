#include <iostream>
#include <mutex>

using std::mutex;
using std::lock_guard;

struct ThreadSafeCoutSection : std::ostream {
  lock_guard<mutex> lock;
  ThreadSafeCoutSection(mutex& mut) : lock(mut) {
  }

  struct Endl {};

  template <typename T>
  ThreadSafeCoutSection& operator<<(T&& x) {
    std::cout << std::forward<T>(x);
    return *this;
  }

  ThreadSafeCoutSection& operator<<(Endl) {
    std::cout << std::endl;
    return *this;
  }
};

struct ThreadSafeCout {
  mutex mut;

  template <typename T>
  ThreadSafeCoutSection& operator<<(T&& x) {
    return ThreadSafeCoutSection(mut) << std::forward<T>(x);
  }
};

static ThreadSafeCout cout;
static ThreadSafeCoutSection::Endl endl;

int main() {
  cout << "OK" << endl;
}
