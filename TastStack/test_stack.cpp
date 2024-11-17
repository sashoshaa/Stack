#include "../Lab3/TStack.h"
#include "gtest.h"

TEST(TStack, can_create_stack_with_positive_size)
{
	// ��������, ��� ����� ������� ���� � ������������� ��������

	ASSERT_NO_THROW(TStack<int> stack(5));
}
TEST(TStack, can_create_stack_with_positive_length)
{
	// ��������, ��� ����� ������� ���� � ������������� ������

	ASSERT_NO_THROW(TStack<int> stack(10));
}
TEST(TStack, cant_create_too_large_stack)
{
	// ��������, ��� ���� � �������� ������ MAXS ����������� ����������

	ASSERT_ANY_THROW(TStack<int> stack(MAXS + 1));
}
TEST(TStack, throws_when_create_stack_with_negative_length)
{
	// ��������, ��� ���� � ������������� �������� ����������� ����������

	ASSERT_ANY_THROW(TStack<int> stack(-5));
}
TEST(TStack, can_create_copied_stack)
{
	// ��������, ��� ����� ������� ����� �����

	TStack<int> stack(5);
	ASSERT_NO_THROW(TStack<int> stack_copy(stack));
}
TEST(TStack, copied_stack_is_equal_to_source_one)
{
	// ��������, ��� ������������� ���� ����� ���������

	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	TStack<int> stack_copy(stack);
	EXPECT_EQ(stack, stack_copy); // �������� �� ���������

}
TEST(TStack, copied_stack_has_its_own_memory)
{
	// ��������, ��� ������������� ���� ����� ����������� ������

	TStack<int> stack(5);
	stack.Push(1);
	TStack<int> stack_copy(stack);
	stack_copy.Push(2);
	EXPECT_NE(stack.Top(), stack_copy.Top()); // ��������, ��� ����� ����������� �� ������� ���������

}
TEST(TStack, can_push_and_pop_elements_in_lifo_order)
{
	// ��������, ��� �������� ����������� � ��������� � ������� LIFO (Last In First Out)
	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	EXPECT_EQ(stack.Pop(), 3); // ��������� ����������� �������

	EXPECT_EQ(stack.Pop(), 2); // ��������� �� �������

	EXPECT_EQ(stack.Pop(), 1); // ������ ����������� �������

}
TEST(TStack, throws_when_popping_from_empty_stack)
{
	// ��������, ��� ��� ������� ������� ������� �� ������� ����� ������������� ����������

		TStack<int> stack(5);
	ASSERT_ANY_THROW(stack.Pop());
}
TEST(TStack, can_check_if_stack_is_empty)
{
	// ��������, ��� ����� ���������, ���� �� ����

	TStack<int> stack(5);
	EXPECT_TRUE(stack.Empty()); // ������ ����

	stack.Push(1);
	EXPECT_FALSE(stack.Empty()); // ���� �� ���� ����� ���������� ��������

}
TEST(TStack, throws_when_pushing_into_full_stack)
{
	// ��������, ��� ��� ������� �������� ������� � ������ ���� ������������� ����������

		TStack<int> stack(2);
	stack.Push(1);
	stack.Push(2);
	ASSERT_ANY_THROW(stack.Push(3));
}
TEST(TStack, can_clear_stack)
{
	// ��������, ��� ����� �������� ����

	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	stack.Clear(); // ������� �����

	EXPECT_TRUE(stack.Empty()); // ���� ������ ���� ����

}
TEST(TStack, stacks_with_different_sizes_are_not_equal)
{
	// ��������, ��� ����� � ������� ��������� �� �����

	TStack<int> stack1(5);
	TStack<int> stack2(3);
	EXPECT_FALSE(stack1 == stack2); // ���� � �������� 5 � ���� � �������� 3 �� �����

}
TEST(TStack, can_assign_stack_to_itself)
{
	// ��������, ��� ����� ��������� ���� ������ ����

	TStack<int> stack(5);
	stack.Push(1);
	ASSERT_NO_THROW(stack = stack); // ������������ ������ ���� ������ ���� ����������

}
TEST(TStack, can_assign_stacks_of_equal_size)
{
	// ��������, ��� ����� ����������� ������� ����� �����������

	TStack<int> stack1(5);
	stack1.Push(1);
	TStack<int> stack2(5);
	ASSERT_NO_THROW(stack2 = stack1); // ������������ ����� ������ ���� ����������

	EXPECT_EQ(stack2.Pop(), 1); // ��������, ��� �������� ����������� ���������

}
TEST(TStack, can_assign_stacks_of_different_size)
{
	// ��������, ��� ����� ����������� ����� ������ �������� (��� ������� ��� ������ ������������ ����� ������ ��� �����)
	TStack<int> stack1(5);
	stack1.Push(1);
	TStack<int> stack2(3);
	ASSERT_NO_THROW(stack2 = stack1); // ������������ ����� � ������� �������� � �������

		EXPECT_EQ(stack2.Pop(), 1); // ��������, ��� �������� ����������� ���������

}
TEST(TStack, compare_equal_stacks_return_true)
{
	// ��������, ��� ��� ���������� ����� �����

	TStack<int> stack1(5);
	TStack<int> stack2(5);
	stack1.Push(1);
	stack2.Push(1);
	EXPECT_TRUE(stack1 == stack2); // ��������, ��� ����� �����

}


TEST(TStack, throws_when_accessing_top_on_empty_stack)
{
	// ��������, ��� ��� ������� � �������� �������� ������� ����� ������������� ����������

	TStack<int> stack(5);
	ASSERT_ANY_THROW(stack.Top()); // ������ ����, ��������� � �������� �������� ������ ��������� ����������
}

TEST(TStack, can_peek_top_element_without_removing)
{
	// ��������, ��� ����� ���������� �� ������� ������� ��� ��������

	TStack<int> stack(5);
	stack.Push(10);

	EXPECT_EQ(stack.Top(), 10); // ��������, ��� Top ���������� ������� �������
	EXPECT_FALSE(stack.Empty()); // ��������, ��� ������� �� ��� ������
}

TEST(TStack, full_stack_reports_as_full)
{
	// ��������, ��� ������ ���� ���������� true ��� ������ Full

	TStack<int> stack(2);
	stack.Push(1);
	stack.Push(2);

	EXPECT_TRUE(stack.Full()); // ��������, ��� ���� ������������ ��� ������
}


TEST(TStack, empty_stacks_of_same_size_are_equal) 
{
	//������ ���� ����� ������� ������� ����� ������ �� �������
	TStack<int> stack1(5);
	TStack<int> stack2(5);
	EXPECT_EQ(stack1, stack2); // ���������, ��� ������ ����� �����
}


TEST(TStack, copying_stack_does_not_modify_original) 
{
	//����������� ����� �� �������� �������� ����
	TStack<int> stack(3);
	stack.Push(1);
	stack.Push(2);

	TStack<int> copy(stack);
	copy.Pop(); // ��������� ������� �� �����

	EXPECT_EQ(stack.Top(), 2); // ���������, ��� �������� ���� ������� ����������
}


TEST(TStack, can_push_and_check_top) 
{
	// ���������� ��������, �������� Top � Pop
	TStack<int> stack(5);
	stack.Push(10);
	EXPECT_EQ(stack.Top(), 10); // �������� �������� ��������
	EXPECT_EQ(stack.Pop(), 10); // �������� ���������� ���� �� ��������
	EXPECT_TRUE(stack.Empty()); // ���������, ��� ���� ����
}


TEST(TStack, clear_works_correctly_on_non_empty_stack) 
{
	// �������� ������� ����� � ����������� ����������
	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Clear(); // ������� �����
	EXPECT_TRUE(stack.Empty()); // ���������, ��� ���� ����
	EXPECT_ANY_THROW(stack.Pop()); // ������� ������� ������� ������ ��������� ����������
}

//________________________________________________________________________________________________

// �������� ������ ��� ���������� ����������� ������
TEST(TCalc, throws_on_missing_open_bracket) {
	TCalc c;
	c.SetInfix("3+5)*2");
	ASSERT_ANY_THROW(c.ToPostfix());
}

// �������� ������ ��� ���������� ����������� ������
TEST(TCalc, throws_on_missing_close_bracket) {
	TCalc c;
	c.SetInfix("(3+5*2");
	ASSERT_ANY_THROW(c.ToPostfix());
}

// �������� ������ ��� ������������ ������� ������
TEST(TCalc, throws_on_incorrect_bracket_order) {
	TCalc c;
	c.SetInfix(")(3+5)(");
	ASSERT_ANY_THROW(c.ToPostfix());
}

// �������� ���� ������������� �����
TEST(TCalc, can_add_two_positive_numbers) {
	TCalc c;
	c.SetInfix("3+5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 8);
}

// �������� �������������� � �������������� �����
TEST(TCalc, can_add_negative_and_positive_numbers) {
	TCalc c;
	c.SetInfix("(-4)+2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -2);
}

// �������� � ��������� ������������� �����
TEST(TCalc, can_add_and_subtract_positive_numbers) {
	TCalc c;
	c.SetInfix("6+3-5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 4);
}

// ��������� �������������� ����� �� ��������������
TEST(TCalc, can_subtract_from_negative_number) {
	TCalc c;
	c.SetInfix("(-3)-2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -5);
}

// �������� � ��������� � ����������� ������
TEST(TCalc, can_handle_parentheses_with_addition_and_multiplication) {
	TCalc c;
	c.SetInfix("(5+6)*2-3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 19);
}

// ���������� � ������� � ���������
TEST(TCalc, can_handle_exponentiation_and_multiplication) {
	TCalc c;
	c.SetInfix("(4^3+2)*5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 330);
}

// ���������, ��������� � ���������� � �������
TEST(TCalc, can_handle_subtraction_multiplication_and_exponentiation) {
	TCalc c;
	c.SetInfix("(7-2)*3-6^2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -21);
}


// ������� ���� ������������� �����
TEST(TCalc, can_divide_two_positive_numbers) {
	TCalc c;
	c.SetInfix("6/2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 3);
}

// ��������� � ������� ������� � ������
TEST(TCalc, can_handle_unary_minus_at_start) {
	TCalc c;
	c.SetInfix("-3+5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 2);
}


// ��������� � ���������� ��������
TEST(TCalc, can_handle_nested_parentheses) {
	TCalc c;
	c.SetInfix("(3+(4*2))-(7/(1+1))");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 7); // (3 + 8) - (7 / 2) = 7
}

// ��������� � ����������� � ������� � ������������� ����������
TEST(TCalc, can_handle_negative_base_exponentiation) {
	TCalc c;
	c.SetInfix("(-2)^3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -8);
}

// ������� �� ���� �������� ����������
TEST(TCalc, throws_when_dividing_by_zero) {
	TCalc c;
	c.SetInfix("5/0");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix()); // ��������� ����������
}

// ������� ��������� � �������������� ������� � ��������
TEST(TCalc, can_handle_complex_expression_with_negatives) {
	TCalc c;
	c.SetInfix("(-5+1)*(3-4)");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 4);
}

TEST(TCalc, can_handle_negative_in_parentheses) {
	TCalc c;
	c.SetInfix("(-3+5)*2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 4);  // (-3+5)*2 = 4
}

// ���������� ����������� ����� �� �������������� ����� �������� ����������
TEST(TCalc, throws_when_sqrt_of_negative_number) {
	TCalc c;
	c.SetInfix("(-9)^(1/2)");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix());  // ��������� ���������� ��� ���������� ����� �� �������������� �����
}


