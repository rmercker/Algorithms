#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>

using namespace std;

void levelorder(int **arr, int k);

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int n = 0;
	cin >> n;
	int **tree = new int *[n];

	for (int i = 0; i < n; i++) {
		tree[i] = new int[3];
		cin >> tree[i][0] >> tree[i][1] >> tree[i][2];
	}

	levelorder(tree, 0);

	return 0;
}

void levelorder(int **arr, int k) {
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
