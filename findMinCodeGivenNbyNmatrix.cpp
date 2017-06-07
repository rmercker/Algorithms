#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

int main(void) {
	std::ios_base::sync_with_stdio(false);

	int n = 0;
	string hint;

	getline(cin, hint);
	cin >> n;
	cin.ignore();

	string *nBYn = new string[n];
	int *row = new int[n], *col = new int[n], *val = new int[n];
	int j = 0;
	while (j < n) {
		getline(cin, nBYn[j]);
		j++;
	}
	// end input

	// start matix search
		// searching rows first
		
	string temp = "";
	int i = 0, p, count, l, r;
	while (i < n) {
		p = 1;
		j = 0;
		count = 0;
		l = 0;
		r = 0;
		val[0] = 0;
		temp = hint + "@" + nBYn[i];
		while (p < n + hint.size() + 1) {
			// need ifs and to keep track of r and l
			if (p < r) {
				// p is in new found substr
				if (val[p - l] < r - p) {
					val[p] = val[p - l];
					if (val[p] == hint.size()) {
						count++;
					}
				}
				else {
					l = p;
					j = r - p;
					while (temp[r] == temp[j]) { 
						r++;
						j++;
					}
					j = 0;
					val[p] = r - l;
					if (val[p] == hint.size()) {
						count++;
					}
				}
			}
			else {
				if (temp[p] == temp[j]) {
					l = p;
					r = p;
					while (temp[++r] == temp[++j]) { }	// r is one past last valid substr
					j = 0;
					val[p] = r - l;
					if (val[p] == hint.size()) {
						count++;
					}
				}
				else {
					val[p] = 0;
				}
			}
			p++;
		}
		row[i] = count;
		i++;
	}
	
		// searching cols second
	i = 0;
	while (i < n) {
		p = 1;
		j = 0;
		count = 0;
		l = 0;
		r = 0;
		val[0] = 0;
		// temp must be built differently for col evaluation
		temp = hint + '@';
		for (int cols = 0; cols < n; cols++) {
			temp += nBYn[cols].at(i);
		}
		//end temp build
		while (p < n + hint.size() + 1) {
			// need ifs and to keep track of r and l
			if (p < r) {
				// p is in new found substr
				if (val[p - l] < r - p) {
					val[p] = val[p - l];
					if (val[p] == hint.size()) {
						count++;
					}
				}
				else {
					l = p;
					j = r - p;
					while (temp[r] == temp[j]) {
						r++;
						j++;
					}
					j = 0;
					val[p] = r - l;
					if (val[p] == hint.size()) {
						count++;
					}
				}
			}
			else {
				if (temp[p] == temp[j]) {
					l = p;
					r = p;
					while (temp[++r] == temp[++j]) {}	// r is one past last valid substr
					j = 0;
					val[p] = r - l;
					if (val[p] == hint.size()) {
						count++;
					}
				}
				else {
					val[p] = 0;
				}
			}
			p++;
		}
		col[i] = count;
		i++;
	}
	// end matrix search


	// finding length of max combo
	int **maxSize = new int *[n + 1];

	for (int g = n; g >= 0; g--) {
		maxSize[g] = new int[n + 1];
		for (int f = n; f >= 0; f--) {
			if (g == n || f == n) {
				maxSize[g][f] = 0;
			}
			else if (row[g] == col[f]) {
				maxSize[g][f] = 1 + maxSize[g + 1][f + 1];
			}
			else {
				maxSize[g][f] = max(maxSize[g][f + 1], maxSize[g + 1][f]);
			}
		}
	}

	// finding max combo from array

	int *combo = new int[maxSize[0][0]];
	int c = 0;
	for (int g = 0, f = 0; g < n && f < n;) {
		if (row[g] == col[f]) {
			combo[c] = row[g];
			c++;
			g++;
			f++;
		}
		else if (maxSize[g][f + 1] >= maxSize[g + 1][f]) {
			f++;
		}
		else {
			i++;
		}
	}
	// printing answer
	/*for (int x = 0; x < maxSize[0][0]; x++) {
		cout << combo[x] << " ";
	}*/

	system("pause");
	return 0;
}
