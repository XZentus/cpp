#include <iostream>
#include <ios>

#include <vector>

const size_t LIMIT = 10000;

using namespace std;

bool is_amicable(unsigned n, const vector<unsigned> & db) {
  const auto & next = db[n];
  if(next == n || next >= LIMIT || db[next] != n)
    return false;
  return true;
}

void fill_db(vector<unsigned> & db) {
  for(unsigned d = 2; d * 2 < LIMIT; d += 1)
    for(unsigned n = d * 2; n < LIMIT; n += d)
      db[n] += d;
}

unsigned count_amicables(const vector<unsigned> & db) {
  unsigned result = 0;
  for(unsigned i = 1; i < LIMIT; i += 1)
    if(is_amicable(i, db))
      result += i;
  return result;
}

int main() {
  ios::sync_with_stdio(false);

  vector<unsigned> divs_sum(LIMIT, 1);
  fill_db(divs_sum);

  cout << count_amicables(divs_sum) << endl;

  return 0;
}
