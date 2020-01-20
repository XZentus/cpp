#include <iostream>
#include <chrono>
#include <thread>
#include <future>

using namespace std;

int slow_function(int time, bool verbose) {
  while (time-- > 0) {
    if (verbose)
      cout << "SLOW ... " << time << " seconds left\n";
    this_thread::yield();
    this_thread::sleep_for(1s);
  }
  return 0;
}

int main() {
  auto f = async(launch::async, slow_function, 5, 1);

  int i = 100500;
  while (i != 0) {
    cin >> i;
    cout << "i^2 = " << i*i << endl;
  }

  return 0;
}
