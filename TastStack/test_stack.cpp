#include "../Lab3/TStack.h"
#include "gtest.h"

TEST(TStack, can_create_stack_with_positive_size)
{
	// Проверка, что можно создать стек с положительным размером

	ASSERT_NO_THROW(TStack<int> stack(5));
}
TEST(TStack, can_create_stack_with_positive_length)
{
	// Проверка, что можно создать стек с положительной длиной

	ASSERT_NO_THROW(TStack<int> stack(10));
}
TEST(TStack, cant_create_too_large_stack)
{
	// Проверка, что стек с размером больше MAXS выбрасывает исключение

	ASSERT_ANY_THROW(TStack<int> stack(MAXS + 1));
}
TEST(TStack, throws_when_create_stack_with_negative_length)
{
	// Проверка, что стек с отрицательным размером выбрасывает исключение

	ASSERT_ANY_THROW(TStack<int> stack(-5));
}
TEST(TStack, can_create_copied_stack)
{
	// Проверка, что можно создать копию стека

	TStack<int> stack(5);
	ASSERT_NO_THROW(TStack<int> stack_copy(stack));
}
TEST(TStack, copied_stack_is_equal_to_source_one)
{
	// Проверка, что скопированный стек равен исходному

	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	TStack<int> stack_copy(stack);
	EXPECT_EQ(stack, stack_copy); // Проверка на равенство

}
TEST(TStack, copied_stack_has_its_own_memory)
{
	// Проверка, что скопированный стек имеет собственную память

	TStack<int> stack(5);
	stack.Push(1);
	TStack<int> stack_copy(stack);
	stack_copy.Push(2);
	EXPECT_NE(stack.Top(), stack_copy.Top()); // Проверка, что стеки различаются по верхним элементам

}
TEST(TStack, can_push_and_pop_elements_in_lifo_order)
{
	// Проверка, что элементы добавляются и удаляются в порядке LIFO (Last In First Out)
	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	EXPECT_EQ(stack.Pop(), 3); // Последний добавленный элемент

	EXPECT_EQ(stack.Pop(), 2); // Следующий по порядку

	EXPECT_EQ(stack.Pop(), 1); // Первый добавленный элемент

}
TEST(TStack, throws_when_popping_from_empty_stack)
{
	// Проверка, что при попытке извлечь элемент из пустого стека выбрасывается исключение

		TStack<int> stack(5);
	ASSERT_ANY_THROW(stack.Pop());
}
TEST(TStack, can_check_if_stack_is_empty)
{
	// Проверка, что можно проверить, пуст ли стек

	TStack<int> stack(5);
	EXPECT_TRUE(stack.Empty()); // Пустой стек

	stack.Push(1);
	EXPECT_FALSE(stack.Empty()); // Стек не пуст после добавления элемента

}
TEST(TStack, throws_when_pushing_into_full_stack)
{
	// Проверка, что при попытке добавить элемент в полный стек выбрасывается исключение

		TStack<int> stack(2);
	stack.Push(1);
	stack.Push(2);
	ASSERT_ANY_THROW(stack.Push(3));
}
TEST(TStack, can_clear_stack)
{
	// Проверка, что можно очистить стек

	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	stack.Clear(); // Очистка стека

	EXPECT_TRUE(stack.Empty()); // Стек должен быть пуст

}
TEST(TStack, stacks_with_different_sizes_are_not_equal)
{
	// Проверка, что стеки с разными размерами не равны

	TStack<int> stack1(5);
	TStack<int> stack2(3);
	EXPECT_FALSE(stack1 == stack2); // Стек с размером 5 и стек с размером 3 не равны

}
TEST(TStack, can_assign_stack_to_itself)
{
	// Проверка, что можно присвоить стек самому себе

	TStack<int> stack(5);
	stack.Push(1);
	ASSERT_NO_THROW(stack = stack); // Присваивание самого себя должно быть безопасным

}
TEST(TStack, can_assign_stacks_of_equal_size)
{
	// Проверка, что стеки одинакового размера можно присваивать

	TStack<int> stack1(5);
	stack1.Push(1);
	TStack<int> stack2(5);
	ASSERT_NO_THROW(stack2 = stack1); // Присваивание стека должно быть безопасным

	EXPECT_EQ(stack2.Pop(), 1); // Проверка, что элементы скопированы правильно

}
TEST(TStack, can_assign_stacks_of_different_size)
{
	// Проверка, что можно присваивать стеки разных размеров (при условии что размер принимающего стека больше или равен)
	TStack<int> stack1(5);
	stack1.Push(1);
	TStack<int> stack2(3);
	ASSERT_NO_THROW(stack2 = stack1); // Присваивание стека с большим размером в меньший

		EXPECT_EQ(stack2.Pop(), 1); // Проверка, что элементы скопированы правильно

}
TEST(TStack, compare_equal_stacks_return_true)
{
	// Проверка, что два одинаковых стека равны

	TStack<int> stack1(5);
	TStack<int> stack2(5);
	stack1.Push(1);
	stack2.Push(1);
	EXPECT_TRUE(stack1 == stack2); // Проверка, что стеки равны

}


TEST(TStack, throws_when_accessing_top_on_empty_stack)
{
	// Проверка, что при доступе к верхнему элементу пустого стека выбрасывается исключение

	TStack<int> stack(5);
	ASSERT_ANY_THROW(stack.Top()); // Пустой стек, обращение к верхнему элементу должно выбросить исключение
}

TEST(TStack, can_peek_top_element_without_removing)
{
	// Проверка, что можно посмотреть на верхний элемент без удаления

	TStack<int> stack(5);
	stack.Push(10);

	EXPECT_EQ(stack.Top(), 10); // Проверка, что Top возвращает верхний элемент
	EXPECT_FALSE(stack.Empty()); // Проверка, что элемент не был удален
}

TEST(TStack, full_stack_reports_as_full)
{
	// Проверка, что полный стек возвращает true для метода Full

	TStack<int> stack(2);
	stack.Push(1);
	stack.Push(2);

	EXPECT_TRUE(stack.Full()); // Проверка, что стек распознается как полный
}


TEST(TStack, empty_stacks_of_same_size_are_equal) 
{
	//Пустой стек равен другому пустому стеку такого же размера
	TStack<int> stack1(5);
	TStack<int> stack2(5);
	EXPECT_EQ(stack1, stack2); // Ожидается, что пустые стеки равны
}


TEST(TStack, copying_stack_does_not_modify_original) 
{
	//Копирование стека не изменяет исходный стек
	TStack<int> stack(3);
	stack.Push(1);
	stack.Push(2);

	TStack<int> copy(stack);
	copy.Pop(); // Извлекаем элемент из копии

	EXPECT_EQ(stack.Top(), 2); // Ожидается, что исходный стек остался неизменным
}


TEST(TStack, can_push_and_check_top) 
{
	// Добавление элемента, проверка Top и Pop
	TStack<int> stack(5);
	stack.Push(10);
	EXPECT_EQ(stack.Top(), 10); // Проверка верхнего элемента
	EXPECT_EQ(stack.Pop(), 10); // Проверка извлечения того же элемента
	EXPECT_TRUE(stack.Empty()); // Ожидается, что стек пуст
}


TEST(TStack, clear_works_correctly_on_non_empty_stack) 
{
	// Проверка очистки стека с несколькими элементами
	TStack<int> stack(5);
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Clear(); // Очистка стека
	EXPECT_TRUE(stack.Empty()); // Ожидается, что стек пуст
	EXPECT_ANY_THROW(stack.Pop()); // Попытка извлечь элемент должна выбросить исключение
}

//________________________________________________________________________________________________

// Проверка ошибки при отсутствии открывающей скобки
TEST(TCalc, throws_on_missing_open_bracket) {
	TCalc c;
	c.SetInfix("3+5)*2");
	ASSERT_ANY_THROW(c.ToPostfix());
}

// Проверка ошибки при отсутствии закрывающей скобки
TEST(TCalc, throws_on_missing_close_bracket) {
	TCalc c;
	c.SetInfix("(3+5*2");
	ASSERT_ANY_THROW(c.ToPostfix());
}

// Проверка ошибки при неправильном порядке скобок
TEST(TCalc, throws_on_incorrect_bracket_order) {
	TCalc c;
	c.SetInfix(")(3+5)(");
	ASSERT_ANY_THROW(c.ToPostfix());
}

// Сложение двух положительных чисел
TEST(TCalc, can_add_two_positive_numbers) {
	TCalc c;
	c.SetInfix("3+5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 8);
}

// Сложение отрицательного и положительного числа
TEST(TCalc, can_add_negative_and_positive_numbers) {
	TCalc c;
	c.SetInfix("(-4)+2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -2);
}

// Сложение и вычитание положительных чисел
TEST(TCalc, can_add_and_subtract_positive_numbers) {
	TCalc c;
	c.SetInfix("6+3-5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 4);
}

// Вычитание положительного числа из отрицательного
TEST(TCalc, can_subtract_from_negative_number) {
	TCalc c;
	c.SetInfix("(-3)-2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -5);
}

// Сложение и умножение с приоритетом скобок
TEST(TCalc, can_handle_parentheses_with_addition_and_multiplication) {
	TCalc c;
	c.SetInfix("(5+6)*2-3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 19);
}

// Возведение в степень и умножение
TEST(TCalc, can_handle_exponentiation_and_multiplication) {
	TCalc c;
	c.SetInfix("(4^3+2)*5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 330);
}

// Вычитание, умножение и возведение в степень
TEST(TCalc, can_handle_subtraction_multiplication_and_exponentiation) {
	TCalc c;
	c.SetInfix("(7-2)*3-6^2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -21);
}


// Деление двух положительных чисел
TEST(TCalc, can_divide_two_positive_numbers) {
	TCalc c;
	c.SetInfix("6/2");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 3);
}

// Выражение с унарным минусом в начале
TEST(TCalc, can_handle_unary_minus_at_start) {
	TCalc c;
	c.SetInfix("-3+5");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 2);
}


// Выражение с вложенными скобками
TEST(TCalc, can_handle_nested_parentheses) {
	TCalc c;
	c.SetInfix("(3+(4*2))-(7/(1+1))");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), 7); // (3 + 8) - (7 / 2) = 7
}

// Выражение с возведением в степень и отрицательным основанием
TEST(TCalc, can_handle_negative_base_exponentiation) {
	TCalc c;
	c.SetInfix("(-2)^3");
	c.ToPostfix();
	EXPECT_EQ(c.CalcPostfix(), -8);
}

// Деление на ноль вызывает исключение
TEST(TCalc, throws_when_dividing_by_zero) {
	TCalc c;
	c.SetInfix("5/0");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix()); // Ожидается исключение
}

// Сложное выражение с отрицательными числами и скобками
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

// Извлечение квадратного корня из отрицательного числа вызывает исключение
TEST(TCalc, throws_when_sqrt_of_negative_number) {
	TCalc c;
	c.SetInfix("(-9)^(1/2)");
	c.ToPostfix();
	EXPECT_ANY_THROW(c.CalcPostfix());  // Ожидается исключение при извлечении корня из отрицательного числа
}


