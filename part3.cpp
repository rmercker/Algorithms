#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <queue>

using namespace std;

int **tree;

void makeTree(int *arr, int size, int k);
void levelorder(int **arr);
int findIndex(int *arr, int size, int val);

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int n = 0;
	cin >> n;

	tree = new int *[n];
	int *infix = new int[n];

	for (int p = 0; p < n; p++) {
		tree[p] = new int[3];
	}
	for (int i = n - 1; i >= 0; i--) {
		cin >> tree[i][0];
		tree[i][1] = -1;
		tree[i][2] = -1;
	}
	for (int j = 0; j < n; j++) {
		cin >> infix[j];
	}

	makeTree(infix, n, 0);
	levelorder(tree);

	system("pause");
	return 0;
}

void makeTree(int *arr, int size, int k) {
	int a = findIndex(arr, size, tree[k][0]);
	int *temp;

	if (a == -1) {
		tree[k][1] = -1;
		tree[k][2] = -1;
		return;
	}
	if (size - 1 - a > 0) {
		tree[k][2] = k + 1;
		temp = new int[size - a - 1];
		for (int j = 0; j < size - a - 1; j++) {
			temp[j] = arr[a + 1 + j];
		}
		makeTree(temp, size - a - 1, k + 1);
	}
	else {
		tree[k][2] = -1;
	}
	if (a > 0) {
		tree[k][1] = k + size - a;
		temp = new int[a];
		for (int j = 0; j < a; j++) {
			temp[j] = arr[j];
		}
		makeTree(temp, a, k + size - a);
	}
	else {
		tree[k][1] = -1;
	}
}

int findIndex(int *arr, int size, int val) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == val) {
			return i;
		}
	}
	return -1;
}

void levelorder(int **arr) {
	queue<int> level;
	level.push(0);

	while (!level.empty()) {
		cout << arr[level.front()][0] << " ";
		if (arr[level.front()][1] != -1) {
			level.push(arr[level.front()][1]);
		}
		if (arr[level.front()][2] != -1) {
			level.push(arr[level.front()][2]);
		}
		level.pop();
	}
}