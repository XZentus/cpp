#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

#include <cstdlib>
#include <ctime>

using namespace std;

typedef int INT;

enum vector_type {vec_random, vec_constant_1, vec_linear};

vector<INT> create_vector(size_t size, vector_type type = vec_linear) {
  vector<INT> result;
  result.reserve(size);
  switch(type) {
   case vec_random:
     for(size_t i = 0; i < size; ++i)
       result.push_back(rand());
     break;
   case vec_constant_1:
     for(size_t i = 0; i < size; ++i)
       result.push_back(1);
     break;
   case vec_linear:
     for(size_t i = 0; i < size; ++i)
       result.push_back(i);
     break;
  }
  return result;
}

ostream & operator<<(ostream & os, const vector<INT> & v) {

  os << "[ ";
  for(const auto & e : v)
    os << e << ' ';
  os << ']';
  return os;
}

mutex print_mutex;
struct mutex_handler {
  mutex & _m;
  mutex_handler(mutex &m) : _m(m) {
    _m.lock();
  };
  ~mutex_handler() {
    _m.unlock();
  };
  mutex_handler() = delete;
};

class AccumFunctor {
  public:
    void operator() (const vector<INT> & v,
                     size_t from = 0,
                     size_t to = ~(INT)0) {
      auto thread_id = this_thread::get_id();
      {
        auto m = mutex_handler(print_mutex);
        cout << "Calculation started: 0x" << hex << thread_id << endl;
      }

      result = 0;
      auto iter = v.cbegin() + from, end = v.cend();

      for(size_t i = from; i < to && iter != end; i += 1, iter += 1)
        result += *iter;

      using namespace chrono_literals;
      this_thread::sleep_for(2s);

      {
        auto m = mutex_handler(print_mutex);
        cout << "Calculation end: 0x" << thread_id << endl;
      }
      return;
    }
    INT result;
};

void accum_function(const vector<INT> & v,
                    INT & result,
                    size_t from = 0,
                    size_t to = ~(INT)0) {
  result = 0;
  auto iter = v.cbegin() + from, end = v.cend();

  for(size_t i = from; i < to && iter != end; i += 1, iter += 1)
    result += *iter;

  return;
}

int main() {

  srand(time(0));
  ios::sync_with_stdio(false);

  auto v = create_vector(20000, vec_random);

  //  cout << "Initial_vector: " << v << endl;

  auto acm1 = AccumFunctor(), acm2 = AccumFunctor();
  thread t1(ref(acm1), ref(v), 0,            v.size() / 2);
  thread t2(ref(acm2), ref(v), v.size() / 2, v.size());

  t1.join();
  t2.join();

  cout << dec << acm1.result << ' ' << acm2.result << ' ' << acm1.result + acm2.result << endl;

  return 0;
}
