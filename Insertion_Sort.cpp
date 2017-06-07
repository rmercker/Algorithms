#include <iostream>
#include <cmath>

using namespace std;

int main(void) {

	int *list;
	int N = 0;
	int temp = 0;
	int i = 1;

	cin >> N;

	if (N > 0) {
		list = new int[N];
		cin >> temp;
		list[0] = temp;
		
		while (i < N) {
			cin >> temp;

			for (int j = i; j >= 0; --j) {
				if (temp >= list[j - 1]) {
					list[j] = temp;
					break;
				}
				else {
					list[j] = list[j - 1];
				}
			}

			i++;
		}
		i = 0;
		while (i < N) {
			cout << list[i] << endl;
			i++;
		}
	}
	return 0;
}