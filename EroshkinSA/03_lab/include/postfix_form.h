#ifndef __POSTFIX_FORM_H__
#define __POSTFIX_FORM_H__

#include <iostream>
#include "stack.h"

using namespace std;

bool isOperation(char x) {
	return (x == '+' || x == '-' || x == '/' || x == '*');
}

bool isOperand(char x) {
	return (x >= 'a' && x <= 'z');
}

bool correctness(const string& s) {
	TStack<char> braces(s.size());
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') braces.push(s[i]);
		if (s[i] == ')') {
			if (!braces.isEmpty()) braces.pop();
			else return false;
		}
	}
	if (!braces.isEmpty()) return false;
	if (isOperation(s[0]) && s[0] != '-') return false;
	if (isOperation(s[s.size() - 1])) return false;
	for (int i = 0; i < s.size() - 1; i++){
		if (s[i] == ')' && s[i + 1] == '(') return false;
		if (isOperand(s[i]) && s[i + 1] == '(') return false;
		if (s[i] == ')' && isOperand(s[i + 1])) return false;
		if (isOperation(s[i]) && isOperation(s[i + 1])) return false;
		if (s[i] == '(' &&
			(isOperation(s[i + 1]) && s[i + 1] != '-' || s[i + 1] == ')'))
			return false;
		if (isOperand(s[i]) && isOperand(s[i + 1])) return false;
		if (isOperation(s[i]) && s[i + 1] == ')') return false;
	}
	return true;
}

class ArithmeticExpression {
	string expression, postfix_form = "";
	set<char> operands;
	map<char, double> value;
public:
	ArithmeticExpression(const string& exp) : expression(exp) {
		string compressed = "";
		for (char x : exp) if (x != ' ') compressed += x;
		if (!correctness(compressed))
			throw invalid_argument("Incorrect arithmetic expression!");
		TStack<char> op(compressed.size());
		int i = 0;
		while (i < compressed.size()) {
			if (compressed[i] == ' ') continue;
			if (compressed[i] == '(' && i + 1 < compressed.size() &&
				compressed[i + 1] == '-') {
				op.push('(');
				postfix_form += '0';   // ...(-...) case
				op.push('-');
				i += 2;
				continue;
			}
			if (compressed[i] >= 'a' && compressed[i] <= 'z') {
				postfix_form += compressed[i];
				operands.insert(compressed[i]);
			}
			else {
				if (compressed[i] == ')') {
					while (!op.isEmpty() && op.top() != '(') {
						postfix_form += op.top();
						op.pop();
					}
					assert(op.isEmpty() || (!op.isEmpty() && op.top() == '('));
					if (!op.isEmpty()) op.pop();
				}
				if (compressed[i] == '(') op.push(compressed[i]);
				if (compressed[i] == '/' || compressed[i] == '*') {
					while (!op.isEmpty() &&
						(op.top() == '*' || op.top() == '/')) {
						postfix_form += op.top();
						op.pop();
					}
					op.push(compressed[i]);
				}
				if (compressed[i] == '+' || compressed[i] == '-') {
					while (!op.isEmpty() &&
						(op.top() == '*' || op.top() == '/' ||
						op.top() == '+' || op.top() == '-')) {
						postfix_form += op.top();
						op.pop();
					}
					op.push(compressed[i]);
				}
			}
			i++;
		}
		while (!op.isEmpty()) {
			postfix_form += op.top();
			op.pop();
		}
	}

	double compute() {
		TStack<double> ans(postfix_form.size());
		for (int i = 0; i < postfix_form.size(); i++) {
			if (postfix_form[i] == '0') ans.push(0);
			else if (postfix_form[i] >= 'a' && postfix_form[i] <= 'z')
				ans.push(value[postfix_form[i]]);
			else {
				double op1, op2;
				op1 = ans.top(); ans.pop();
				if (ans.isEmpty() && postfix_form[i] == '-') {
					ans.push(-op1);   // - in the beggining of the expression
					continue;
				}
				op2 = ans.top(); ans.pop();
				switch (postfix_form[i]) {
				case '+':
					ans.push(op2 + op1);
					break;
				case '-':
					ans.push(op2 - op1);
					break;
				case '/':
					if (op1 == 0.0)
						throw invalid_argument("Division by zero!");
					ans.push(op2 / op1);
					break;
				case '*':
					ans.push(op2 * op1);
					break;
				}
			}
		}
		return ans.top();
	}

	void GetValues() {
		double val;
		for (char x : operands) {
			cout << "Insert value of " << x << ":\n";
			cin >> val;
			value[x] = val;
		}
	}

	void GetPostfixForm() const noexcept {
		cout << "Original expression: " << expression << '\n';
		cout << "Postfix form: " << postfix_form << '\n';
	}
};

#endif