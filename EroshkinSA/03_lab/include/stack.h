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


#endif