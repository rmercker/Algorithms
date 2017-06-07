#include <iostream>
#include <cmath>

using namespace std;

int main(void) {
	int arr[50] = { 0, 1, 3, 4, 7, 9, 11, 23, 45, 46, 47, 56, 68, 76, 77, 78, 79, 80, 90, 91, 94, 95, 99, 120, 123, 124, 134, 135, 136, 137, 148, 159, 170, 253, 469, 470, 480, 490, 501, 756, 834, 843, 952, 1008, 1009, 1010, 1011, 1220, 1330, 2001 };
	int N = 0;

	while (N >= 0) {
		cin >> N;

		int i = 0;
		int j = 49;

		while (i < j) {
			if (arr[i + ((j - i) / 2)] == N) {
				cout << "Found" << endl;
				break;
			}
			else if (arr[i + ((j - i) / 2)] < N) {
				i = i + ((j - i) / 2) + 1;
			}
			else {
				j = i + ((j - i) / 2);
			}
		}
		if (i >= j) {
			cout << "Not Found";
		}
	}

	system("pause");
	return 0;
}