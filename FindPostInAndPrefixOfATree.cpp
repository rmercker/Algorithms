#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void infix(int **arr, int k);
void prefix(int **arr, int k);
void postfix(int **arr, int k);

int main(void) {
	std::ios_base::sync_with_stdio(false);
	
	int n = 0;
	cin >> n;
	int **tree = new int *[n];

	for (int i = 0; i < n; i++) {
		tree[i] = new int[3];
		cin >> tree[i][0] >> tree[i][1] >> tree[i][2];
	}

	prefix(tree, 0);
	cout << '\n';
	infix(tree, 0);
	cout << '\n';
	postfix(tree, 0);

	return 0;
}

void infix(int **arr, int k) {
	if (arr[k][1] != -1) {
		infix(arr, arr[k][1]);
	}
	cout << arr[k][0] << " ";
	if (arr[k][2] != -1) {
		infix(arr, arr[k][2]);
	}
}

void prefix(int **arr, int k) {
	cout << arr[k][0] << " ";
	if (arr[k][1] != -1) {
		prefix(arr, arr[k][1]);
	}
	if(arr[k][2] != -1) {
		prefix(arr, arr[k][2]);
	}
}

void postfix(int **arr, int k) {
	if (arr[k][1] != -1) {
		postfix(arr, arr[k][1]);
	}
	if (arr[k][2] != -1) {
		postfix(arr, arr[k][2]);
	}
	cout << arr[k][0] << " ";
}
