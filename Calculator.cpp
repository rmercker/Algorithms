#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;

string solve(unordered_map<string, string> var, string expression, bool isExp);
double giveValue(double val, double val2, char op);

int main(void) {
	std::ios_base::sync_with_stdio(false);

	string statement;
	unordered_map<string, string> variables;


	variables["Pi"] = "3.14169";	// check to ensure this is ok!
	variables["e"] = "2.718";

	getline(cin, statement);

	while (statement != "quit") {	//checking for exit command

		int i = 0;
		while (statement.at(i) == ' ') { //finding first non space character
			i++;
		}

		if (statement.substr(i, 3) == "let" && statement.at(i + 3) == ' ') { // checking for assignment and then determining variable name and then passing expression into solve function
			i += 4;
			while (statement.at(i) == ' ') {
				i++;
			}
			string temp;

			int j = i;

			while (((int)statement.at(j) <= 90 && (int)statement.at(j) >= 65) || ((int)statement.at(j) <= 122 && (int)statement.at(j) >= 97)) {		//finds whole variable name
				j++;
			}

			temp = statement.substr(i, j - i);	//sets temp to variable substring
			i = j;

			while (statement.at(i) != '=') {	// finds where the following expression begins and passes it to solve function
				i++;
			}

			string answer = solve(variables, statement.substr(i + 1, statement.length() - i + 1), 0);
			if (answer != "Undeclared-Variable" && answer != "Division-By-Zero") {
				variables[temp] = answer;	// inserts new variable or updates existing variable assuming no errors from the solve function
			}
		}

		string answer = (solve(variables, statement, 1));
		if ( answer != "good") {
			cout << answer << '\n';
			}
		//else {	// there is no assignment, this is just an expression
		//	string answer = (solve(variables, statement));
		//	if (answer == "Undeclared-Variable" || answer == "Division-By-Zero") {
		//		cout << answer << '\n';
		//	}
		//	else {
		//		cout << stod(solve(variables, statement)) << '\n';
		//	}
		//}

		getline(cin, statement);
	}

	return 0;
}

string solve(unordered_map<string, string> var, string expression, bool isExp) {		// function used to translate an expression into a value to be assigned or output
	
	int i = 0;

	while (i < expression.length()) {	// checking for variables and condensing functions to one letter form
		if (expression.at(i) == ' ') {
			expression.erase(expression.begin() + i);
			if (i >= expression.length()) {
				break;
			}
		}
		else if (!(((int)expression.at(i) <= 90 && (int)expression.at(i) >= 65) || ((int)expression.at(i) <= 122 && (int)expression.at(i) >= 97))) {
			i++;
			if (i >= expression.length()) {
				break;
			}
		}
		else {
			int j = i;

			while (((int)expression.at(j) <= 90 && (int)expression.at(j) >= 65) || ((int)expression.at(j) <= 122 && (int)expression.at(j) >= 97)) {	//determines length of variable
				j++;
				if (j >= expression.length()) {
					break;
				}
			}

			if (expression.substr(i, j - i) == "sin" || expression.substr(i, j - i) == "cos" || expression.substr(i, j - i) == "log") {	//usefull for infix to postfix notation
				expression.erase(expression.begin() + i + 1);
				expression.erase(expression.begin() + i + 1);
				i = i + 1;
			}
			else if (var.find(expression.substr(i, j - i)) == var.end()){
				return "Undeclared-Variable";
			}
			else {
				expression.replace(i, j - i, var[expression.substr(i, j - i)]);
				i += var[expression.substr(i, j - i)].length();	// sets i to one after previous replace
			}
			 
		}
		
	}

	// expression calculations using stack to put into postfix and then evaluating, where s, c, and l are operators preforming sin, cos, and log respectively
	
	stack<double> num;	// numbers in expression
	stack<char> op;	// operations in expression

	i = 0;
	size_t sz;

	while (i < expression.length() || !op.empty()) {	//ends when whole expression is read and op stack is empty
		
			if (i < expression.length() && expression.at(i) == ')') {
				if (!op.empty() && op.top() == '(') {
					op.pop();
					i++;
				}
				else {
					if (op.top() == 's' || op.top() == 'c' || op.top() == 'l') {
						double x = giveValue(num.top(), 0, op.top());
						num.pop();
						num.push(x);
						op.pop();
					}
					else {
						double y = num.top();
						if (y == 0 && op.top() == '/') {
							return "Division-By-Zero";
						}
						num.pop();
						double x = giveValue(y, num.top(), op.top());
						num.pop();
						num.push(x);
						op.pop();
					}
				}
			}
			
			if (i < expression.length() && (expression.at(i) == 's' || expression.at(i) == 'c' || expression.at(i) == 'l' || expression.at(i) == '(')) {		// is the operator one of these
				if (expression.at(i) != '(') {
					op.push(expression.at(i));
					i++;
				}
				op.push(expression.at(i));
				i++;
			}
			if (i < expression.length() && expression.at(i) <= 57 && expression.at(i) >= 48){
				num.push(stod(expression.substr(i), &sz));	// pushes in number
				i = expression.length() - (expression.substr(i).length() - sz);
			}
			if (i < expression.length() && expression.at(i) == '^') {	// is the operator one of these
				if (op.empty() || (op.top() != 's' && op.top() != 'c' && op.top() != 'l')) {
					op.push(expression.at(i));
					i++;
				}
				else {
					double x = giveValue(num.top(), 0, op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
			}
			if (i < expression.length() && (expression.at(i) == '*' || expression.at(i) == '/')) { // is the operator one of these
				if ((op.empty() || op.top() == '(' || op.top() == '+' || op.top() == '-')) {
					op.push(expression.at(i));
					i++;
				}
				else if (op.top() == 's' || op.top() == 'c' || op.top() == 'l') {
					double x = giveValue(num.top(), 0, op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
				else {
					double y = num.top();
					if (y == 0 && op.top() == '/') {
						return "Division-By-Zero";
					}
					num.pop();
					double x = giveValue(y, num.top(), op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
			}
			if (i < expression.length() && (expression.at(i) == '+' || expression.at(i) == '-')) { // is the operator one of these
				if ((op.empty() || op.top() == '(')) {
					op.push(expression.at(i));
					i++;
				}
				else if (op.top() == 's' || op.top() == 'c' || op.top() == 'l') {
					double x = giveValue(num.top(), 0, op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
				else {
					double y = num.top();
					if (y == 0 && op.top() == '/') {
						return "Division-By-Zero";
					}
					num.pop();
					double x = giveValue(y, num.top(), op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
			}
			if (i >= expression.length() && !op.empty()) {
				if (op.top() == 's' || op.top() == 'c' || op.top() == 'l') {
					double x = giveValue(num.top(), 0, op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
				else {
					double y = num.top();
					if (y == 0 && op.top() == '/') {
						return "Division-By-Zero";
					}
					num.pop();
					double x = giveValue(y, num.top(), op.top());
					num.pop();
					num.push(x);
					op.pop();
				}
			}
		
	}

	if (isExp) {
		cout << num.top() << '\n';
		return "good";
	}
	return to_string(num.top());
}

double giveValue(double val, double val2, char op) {	// this function takes in the top number, then second from top number and the operator to preform and appropriately computes the value
	double x;
	if (op == 's') {
		 x = sin(val);	
	}
	else if (op == 'c') {
		x = cos(val);
	}
	else if (op == 'l') {
		x = log(val);
	}
	else if (op == '^') {
		x = pow(val2, val);
	}
	else if (op == '*') {
		x = val * val2;
	}
	else if (op == '/') {
		x = val2 / val;
	}
	else if (op == '+') {
		x = val + val2;
	}
	else if (op == '-') {
		x = val2 - val;
	}

	return x;
}