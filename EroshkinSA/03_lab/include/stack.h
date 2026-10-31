#ifndef __TStack_H__
#define __TSTACK_H__

#include <iostream>
#include <cassert>
#include <set>
#include <map>

using namespace std;

const int MAX_STACK_SIZE = 100000000;

template<typename T>
class TStack {
protected:
	size_t sz;
	int top_idx;
	T* pMem;
public:
	TStack(size_t size = 1) : sz(size), top_idx(-1) {
		if (sz == 0) throw out_of_range("Stack size should be greater than zero!");
		if (sz > MAX_STACK_SIZE) throw out_of_range("Too large stack size");
		pMem = new T[sz];
	}

	TStack(const TStack& st) : sz(st.sz), top_idx(st.top_idx) {
		pMem = new T[sz];
		copy(st.pMem, st.pMem + sz, pMem);
	}

	TStack(TStack&& st) : sz(st.sz), top_idx(st.top_idx) {
		pMem = st.pMem;
		st.sz = 0;
		st.top_idx = -1;
		st.pMem = nullptr;
	}

	~TStack() {
		delete[] pMem;
	}

	const TStack& operator=(const TStack& st) {
		if (this == &st) return *this;
		if (sz != st.sz) {
			sz = st.sz;
			T* tmp = new T[sz];
			delete[] pMem;
			pMem = tmp;
		}
		top_idx = st.top_idx;
		copy(st.pMem, st.pMem + sz, pMem);
		return *this;
	}

	TStack& operator=(TStack&& st) {
		sz = st.sz; st.sz = 0;
		top_idx = st.top_idx; st.top_idx = -1;
		pMem = st.pMem; st.pMem = nullptr;
		return *this;
	}

	bool isFull() const noexcept {
		return (top_idx + 1 == sz);
	}

	bool isEmpty() const noexcept {
		return (top_idx == -1);
	}

	T top() const {
		if (isEmpty()) throw invalid_argument("Stack is empty!");
		return pMem[top_idx];
	}

	void pop() {
		if (isEmpty()) throw invalid_argument("Stack is empty!");
		top_idx--;
	}

	void push(T x) {
		if (isFull()) throw invalid_argument("Stack is full!");
		pMem[++top_idx] = x;
	}
};

//______________________________
//______________________________

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
	for (int i = 0; i < s.size() - 1; i++) {
		if ((s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') &&  //
			(s[i + 1] == '+' || s[i + 1] == '-' ||                         // +-
				s[i + 1] == '/' || s[i + 1] == '*') ||                        //__________ 
			(s[i] == '(' &&                                                //
				(s[i + 1] == ')' || s[i + 1] == '+' || s[i + 1] == '*' ||      // (+ , (), (*
					s[i + 1] == '/')) || (s[i] >= 'a' && s[i] <= 'z' &&           //__________
						s[i + 1] >= 'a' && s[i + 1] <= 'z'))                          // ab
			return false;
	}
	return true;
}

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
					if(!op.isEmpty()) op.pop();
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
		cout << postfix_form << endl;
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
			cout << "Insert valur of " << x << ":\n";
			cin >> val;
			value[x] = val;
		}
	}
};

#endif