#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, can_create_vector_with_positive_length_2)
{
	int arr[] = { 2 };
  ASSERT_NO_THROW(TDynamicVector<int> v(arr, 5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, throws_when_create_vector_with_large_length_)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(100000001));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(102);
	TDynamicVector<int> v2(v1);

	ASSERT_EQ(v1, v2);

}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int size = 5;
	TDynamicVector<int> v1(size);
	for (int i = 0; i < size; i++)
		v1[i] = 2;

	TDynamicVector<int> v2(v1);

	v2[0] = 10;

	EXPECT_EQ(2, v1[0]);
	EXPECT_EQ(10, v2[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;
  v[1] = v[0];

  EXPECT_EQ(4, v[0]);
  EXPECT_EQ(v[0], v[1]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	int size = 99;
	TDynamicVector<int> v1(size);
	
	ASSERT_ANY_THROW(v1[-2]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	int size = 99;
	TDynamicVector<int> v1(size);

	ASSERT_ANY_THROW(v1[657]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index_at)
{
	int size = 99;
	TDynamicVector<int> v1(size);

	ASSERT_ANY_THROW(v1.at(-1) = 0);
}
TEST(TDynamicVector, throws_when_set_element_with_too_large_index_at)
{
	int size = 99;
	TDynamicVector<int> v1(size);

	ASSERT_ANY_THROW(v1.at(100) = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int size = 99;
	TDynamicVector<int> v1(size);

	ASSERT_NO_THROW(v1 = v1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int size = 99;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);

	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int size = 9999;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size + 9);

	v1 = v2;

	EXPECT_EQ(v1.size(), v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int size = 99, sz = 70;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(sz);

	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int size = 99;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	v1[2] = 2;
	v2[2] = 2;

	ASSERT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int size = 99;
	TDynamicVector<int> v1(size);
	v1[2] = 2;

	ASSERT_EQ(v1 == v1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int size = 2, sz = 3;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(sz);

	ASSERT_EQ(v1 != v2, true);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);

	v1 = v1 + 2;
	v2[0] = 2;
	v2[1] = 2;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);

	v1 = v1 - 2;
	v2[0] = -2;
	v2[1] = -2;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);

	v1[0] = 1;
	v1[1] = 1;
	v1 = v1 * 3.0;
	v2[0] = 3;
	v2[1] = 3;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	TDynamicVector<int> res(2);
	TDynamicVector<int> result(2);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 3;
	v2[1] = 3;
	result[0] = 4;
	result[1] = 4;

	res = v1 + v2;

	EXPECT_EQ(result, res);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(4);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 3;
	v2[1] = 3;
	v2[3] = 1;

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	TDynamicVector<int> res(2);
	TDynamicVector<int> result(2);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 3;
	v2[1] = 3;
	result[0] = -2;
	result[1] = -2;

	res = v1 - v2;

	EXPECT_EQ(result, res);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(4);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 3;
	v2[1] = 3;
	v2[3] = 1;

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	int res = 0;
	int result = sqrt(6);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 3;
	v2[1] = 3;

	res = v1 * v2;

	EXPECT_EQ(result, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(4);

	v1[0] = 1;
	v1[1] = 1;
	v2[0] = 3;
	v2[1] = 3;
	v2[3] = 1;

	ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, correctly_do_move) 
{
	TDynamicVector<int> v1(2);
	int* tmp = v1.get_pMem();
	TDynamicVector<int> v2(std::move(v1));


	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v1.get_pMem(), nullptr);

	EXPECT_EQ(v2.size(), 2);
	EXPECT_EQ(v2.get_pMem(), tmp);
}

TEST(TDynamicVector, correctly_do_move_operator) {
	TDynamicVector<int> v1(2);
	int* tmp = v1.get_pMem();
	TDynamicVector<int> v2 = std::move(v1);

	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v1.get_pMem(), nullptr);

	EXPECT_EQ(v2.size(), 2);
	EXPECT_EQ(v2.get_pMem(), tmp);

}