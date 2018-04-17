#include <iostream>
#include <string>

using namespace std;

const int N = 256;

void print_arr(int * array) {
	for(int i = 0; i < N; i += 1)
		cout << array[i] << ' ';
	cout << endl;
}

void task_1() {
	int array[N];
	for(int i = 0; i < N; i += 1)
		array[i] = i;
	
	int current_position = 0,
	    skip_size        = 0,
		length;
    char c;
	while(cin >> length) {
		cin >> c;
		
		for(int i = 0; i < length / 2; i += 1) {
			int tmp = array[(current_position + i) % N];
			array[(current_position + i) % N] = array[(current_position + i + length - 1) % N];
			array[(current_position + i + length - 1) % N] = tmp;
		}
		print_arr(array);
		current_position += (length + skip_size) % N;
		skip_size += 1;
			
	}
    cout << array[0] * array[1] << endl;
	return;
}

int main() {
    
	task_1();
	
    return 0;
}
