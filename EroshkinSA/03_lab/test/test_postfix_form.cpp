#include "postfix_form.h"
#include <gtest/gtest.h>

TEST(ArithmeticExpression, can_create_correct_ar_exp) {
	EXPECT_NO_THROW(ArithmeticExpression("(a+b)*c"));
}

TEST(ArithmeticExpression, unfinished_parentheses_sequence) {
	EXPECT_ANY_THROW(ArithmeticExpression("(a+b))"));
}

TEST(ArithmeticExpression, incorrect_parentheses_sequence) {
	EXPECT_ANY_THROW(ArithmeticExpression("(a+(b)"));
}

TEST(ArithmeticExpression, missing_operator_between_brackets) {
	EXPECT_ANY_THROW(ArithmeticExpression("(a+b)(c-d)"));
}

TEST(ArithmeticExpression, cant_start_with_not_unary_minus_operation) {
	EXPECT_ANY_THROW(ArithmeticExpression("*a+(b+c)"));
}

TEST(ArithmeticExpression, can_start_with_unary_minus) {
	EXPECT_NO_THROW(ArithmeticExpression("-a+(b+c)"));
}

TEST(ArithmeticExpression, operand_right_before_bracket_case) {
	EXPECT_ANY_THROW(ArithmeticExpression("a(b+c)"));
}

TEST(ArithmeticExpression, operand_right_after_bracket_case) {
	EXPECT_ANY_THROW(ArithmeticExpression("(b+c)a"));
}

TEST(ArithmeticExpression, two_operations_in_a_row) {
	EXPECT_ANY_THROW(ArithmeticExpression("a(b+-c)"));
}

TEST(ArithmeticExpression, two_operands_in_a_row) {
	EXPECT_ANY_THROW(ArithmeticExpression("a(bc-d)"));
}

TEST(ArithmeticExpression, operation_right_after_bracket) {
	EXPECT_ANY_THROW(ArithmeticExpression("a(*b+c)"));
}

TEST(ArithmeticExpression, can_use_unary_minus_after_bracket) {
	EXPECT_NO_THROW(ArithmeticExpression("a*(-b+c)"));
}

TEST(ArithmeticExpression, operation_right_before_bracket) {
	EXPECT_ANY_THROW(ArithmeticExpression("a(*b+c/)"));
}

TEST(ArithmeticExpression, cant_use_minus_before_bracket) {
	EXPECT_ANY_THROW(ArithmeticExpression("a(b+c-)"));
}

TEST(ArithmeticExpression, cant_end_with_any_operation) {
	EXPECT_ANY_THROW(ArithmeticExpression("-a+(b+c)+"));
}