#include <iostream>
#include <ios>

#include <vector>

const size_t LIMIT = 1000000;

int max_cycle_start, max_cycle_len;

using namespace std;

void fill_db(vector<int> & db) {
  for(int d = 2; d * 2 < LIMIT; d += 1)
    for(int n = d * 2; n < LIMIT; n += d)
      db[n] += d;
}

void fill_chain(const vector<int> & db,
                      vector<int> & result,
                      vector<int> & chain,
                int i) {
    chain.clear();
    do {
        chain.push_back(i);
        i = db[i];
        if(i >= LIMIT || result[i]) {
            for(const auto & e: chain)
                result[e] = -1;
            return;
        }
        
        for(auto iter = chain.cbegin(); iter != chain.cend(); ++iter) {
            if(*iter == i) {
                auto cycle_len = chain.size() - distance(chain.cbegin(), iter);
                cout << "FOUND CYCLE: " << cycle_len << " : ";
                for(auto iter2 = chain.cbegin(); iter2 != iter; ++iter2)
                    result[*iter2] = -1;
                
                do {
                    result[*iter] = cycle_len;
                    cout << *iter << " -> ";
                    ++iter;
                } while(iter != chain.cend());
                
                cout << '(' << i << ")\n";
                if(max_cycle_len < cycle_len) {
                    max_cycle_len = cycle_len;
                    max_cycle_start = i;
                }

                return;
            }
        }
    } while(true);
}

void fill_chains(const vector<int> & divs_sum,
                       vector<int> & result) {
    vector<int> chain;
    chain.reserve(100);
    
    for(int i = 2; i < LIMIT; i += 1)
        if(!result[i])
            fill_chain(divs_sum, result, chain, i);
}

void print_cycle(int len, int start, const vector<int> & db) {
    auto min_i = start, i = start;
    do {
        i = db[i];
        if(min_i > i)
            min_i = i;
    }while(i != start);
    
    
    cout << "\nLength of longest amicable chain : " << len
         << "\nSmallest member : " << min_i << endl;
    i = min_i;
    do {
        cout << i << " -> ";
        i = db[i];
    }while(i != min_i);
    cout << '(' << min_i << ")\n";
}

int main() {
  ios::sync_with_stdio(false);

  vector<int> divs_sum(LIMIT, 1), result(LIMIT, 0);
  fill_db(divs_sum);

  cout << "fill_db() done\n";
  
  fill_chains(divs_sum, result);
  
  print_cycle(max_cycle_len, max_cycle_start, divs_sum);

  return 0;
}
