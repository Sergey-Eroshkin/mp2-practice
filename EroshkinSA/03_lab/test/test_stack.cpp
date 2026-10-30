#include <gtest/gtest.h>
#include "stack.h"

TEST(TStack, can_create_stack_with_positive_length) {
	EXPECT_NO_THROW(TStack<int>(3));
}

TEST(TStack, cant_create_stack_with_negative_length) {
	EXPECT_ANY_THROW(TStack<int>(-3));
}

TEST(TStack, cant_create_too_large_stack) {
	EXPECT_ANY_THROW(TStack<int>(MAX_STACK_SIZE + 1));
}

TEST(TStack, can_create_copied_stack) {
	TStack<int> st(3);
	EXPECT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_is_equal_to_source) {
	TStack<int> st(3);
	st.push(1); st.push(3); st.push(7);
	TStack<int> st1(st);
	for (int i = 0; i < 3; i++) {
		EXPECT_NO_THROW(st.top());
		EXPECT_NO_THROW(st1.top());
		EXPECT_EQ(st1.top(), st.top());
		st1.pop();
		st.pop();
	}
}

TEST(TStack, copied_stack_has_its_own_memory) {
	TStack<int> st(3);
	TStack<int> st1(st);
	st1.push(5);
	st.push(8);
	EXPECT_EQ(st1.top(), 5);
}

TEST(TStack, can_get_top_element) {
	TStack<int> st(3);
	st.push(45);
	EXPECT_EQ(st.top(), 45);
}

TEST(TStack, can_push_element) {
	TStack<int> st(3);
	EXPECT_NO_THROW(st.push(1));
}

TEST(TStack, can_pop_element) {
	TStack<int> st(3);
	st.push(1);
	EXPECT_NO_THROW(st.pop());
}

TEST(TStack, throw_when_push_to_full_stack) {
	TStack<int> st(3);
	st.push(1); st.push(2); st.push(3);
	EXPECT_ANY_THROW(st.push(4));
}

TEST(TStack, throw_when_pop_from_empty_stack) {
	TStack<int> st(3);
	EXPECT_ANY_THROW(st.pop());
}

TEST(TStack, throw_when_try_to_get_top_from_empty_stack) {
	TStack<int> st(3);
	EXPECT_ANY_THROW(st.top());
}

TEST(TStack, top_isnt_pop_element) {
	TStack<int> st(3);
	st.push(1); st.push(2);
	st.top();
	EXPECT_EQ(st.top(), 2);
}

TEST(TStack, empty_stack_is_really_empty) {
	TStack<int> st(3);
	EXPECT_TRUE(st.isEmpty());
}

TEST(TStack, full_stack_is_really_full) {
	TStack<int> st(3);
	st.push(1); st.push(2); st.push(3);
	EXPECT_TRUE(st.isFull());
}

TEST(TStack, regular_stack_isnt_empty) {
	TStack<int> st(3);
	st.push(1); st.push(2);
	EXPECT_FALSE(st.isEmpty());
}

TEST(TStack, regular_stack_isnt_full) {
	TStack<int> st(3);
	st.push(1); st.push(2);
	EXPECT_FALSE(st.isFull());
}