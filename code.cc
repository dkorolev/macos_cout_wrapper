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

int main(int argc, char** argv) {
#if defined(NDEBUG) && !defined(DEBUG)
  cout << "Running the NDEBUG build." << endl;
#elif defined(DEBUG) && !defined(NDEBUG)
  cout << "Running the DEBUG build." << endl;
#else
#error "Must have either `DEBUG` or `NDEBUG` `#define`-d."
#endif

  cout << "OK" << endl;
}
