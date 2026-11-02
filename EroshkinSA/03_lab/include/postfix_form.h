#ifndef __POSTFIX_FORM_H__
#define __POSTFIX_FORM_H__

#include <iostream>
#include "stack.h"

using namespace std;

bool isOperation(char x) {
	return (x == '+' || x == '-' || x == '/' || x == '*');
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
	// make it so!
}  // unarity minus is banned by ADE convention

class ArithmeticExpression {
	string expression, postfix_form = "";
	set<char> operands;
	map<char, double> value;
public:
	ArithmeticExpression(const string& exp) : expression(exp) {
		if (!correctness(exp))
			throw invalid_argument("Incorrect arithmetic expression!");
		TStack<char> op(exp.size());
		int i = 0;
		while (i < exp.size()) {
			if (exp[i] >= 'a' && exp[i] <= 'z') {
				postfix_form += exp[i];
				operands.insert(exp[i]);
			}
			else {
				if (exp[i] == ')') {
					while (!op.isEmpty() && op.top() != '(') {
						postfix_form += op.top();
						op.pop();
					}
					assert(op.isEmpty() || (!op.isEmpty() && op.top() == '('));
					if (!op.isEmpty()) op.pop();
				}
				if (exp[i] == '(') op.push(exp[i]);
				if (exp[i] == '/' || exp[i] == '*') {
					while (!op.isEmpty() && (op.top() == '*' || op.top() == '/')) {
						postfix_form += op.top();
						op.pop();
					}
					op.push(exp[i]);
				}
				if (exp[i] == '+' || exp[i] == '-') {
					while (!op.isEmpty() && (op.top() == '*' || op.top() == '/' ||
						op.top() == '+' || op.top() == '-')) {
						postfix_form += op.top();
						op.pop();
					}
					op.push(exp[i]);
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
			if (postfix_form[i] >= 'a' && postfix_form[i] <= 'z')
				ans.push(value[postfix_form[i]]);
			else {
				double op1, op2;
				op1 = ans.top(); ans.pop();
				op2 = ans.top(); ans.pop();
				switch (postfix_form[i]) {
				case '+':
					ans.push(op2 + op1);
					break;
				case '-':
					ans.push(op2 - op1);
					break;
				case '/':
					if (op1 == 0.0) throw invalid_argument("Division by zero!");
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