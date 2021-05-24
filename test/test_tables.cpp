#pragma once
#include "Table.h"
#include <gtest.h>

TEST(UnorderedTable, can_create_unordered_table_by_constructor_of_default)
{
	ASSERT_NO_THROW(UnorderedTable<> a);
}

TEST(UnorderedTable, can_create_unordered_table_by_constructor_of_copy)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(124, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(21, pol2);
	ASSERT_NO_THROW(UnorderedTable<> b(a));
}

TEST(UnorderedTable, can_insert_in_empty_table)
{
	UnorderedTable<> a; 
	Polynomial pol1("2x^3+4");
	ASSERT_NO_THROW(a.insert(1,pol1));
}

TEST(UnorderedTable, can_insert_in_non_empty_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4");
	ASSERT_NO_THROW(a.insert(42, pol2));
	EXPECT_EQ(2, a.GetSize());
}

TEST(UnorderedTable, throw_then_insert_with_index_existing_in_the_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4");
	ASSERT_ANY_THROW(a.insert(1, pol2));
}

TEST(UnorderedTable, can_erase_element_from_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	ASSERT_NO_THROW(a.erase(1));
	EXPECT_EQ(1, a.GetSize());
}

TEST(UnorderedTable, can_erase_last_element_from_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	a.erase(1);
	ASSERT_NO_THROW(a.erase(42));
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(true, a.empty());
}

TEST(UnorderedTable, throw_when_erase_with_key_which_not_present_in_the_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	ASSERT_ANY_THROW(a.erase(2));
}

TEST(UnorderedTable, can_find_in_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	Polynomial pol3("98y^2z^4+7xz-2x"); a.insert(23, pol3);
	EXPECT_EQ(pol2, a.find(42).second);
	EXPECT_EQ(3, a.GetSize());
}

TEST(UnorderedTable, throw_when_search_for_a_non_existent_entry)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	ASSERT_ANY_THROW(a.find(15));
}

TEST(UnorderedTable, can_clear_table)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	EXPECT_EQ(2, a.GetSize());

	a.clear();
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(true, a.empty());
}

/////////////////////////////////////////////////////////
TEST(OrderedTable, can_create_ordered_table_by_constructor_of_default)
{
	ASSERT_NO_THROW(OrderedTable<> a);
}

TEST(OrderedTable, can_create_ordered_table_by_constructor_of_copy_1)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(124, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(21, pol2);
	ASSERT_NO_THROW(OrderedTable<> b(a));
}

TEST(OrderedTable, can_create_ordered_table_by_constructor_of_copy_2)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(124, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(21, pol2);
	ASSERT_NO_THROW(OrderedTable<> b(a));		//будут в правильном порядке, отсортированы!
}

TEST(OrderedTable, can_insert_in_empty_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4");
	ASSERT_NO_THROW(a.insert(1, pol1));
}

TEST(OrderedTable, can_insert_in_non_empty_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4");
	ASSERT_NO_THROW(a.insert(42, pol2));
	EXPECT_EQ(2, a.GetSize());
}

TEST(OrderedTable, throw_then_insert_with_index_existing_in_the_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4");
	ASSERT_ANY_THROW(a.insert(1, pol2));
}

TEST(OrderedTable, can_erase_element_from_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	ASSERT_NO_THROW(a.erase(1));
	EXPECT_EQ(1, a.GetSize());
}

TEST(OrderedTable, can_erase_last_element_from_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	a.erase(1);
	ASSERT_NO_THROW(a.erase(42));
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(true, a.empty());
}

TEST(OrderedTable, throw_when_erase_with_key_which_not_present_in_the_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	ASSERT_ANY_THROW(a.erase(2));
}

TEST(OrderedTable, can_find_in_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2); a.insert(34, pol2);
	Polynomial pol3("98y^2z^4+7xz-2x"); a.insert(23, pol3);
	EXPECT_EQ(pol2, a.find(34).second);
	EXPECT_EQ(4, a.GetSize());
}

TEST(OrderedTable, throw_when_search_for_a_non_existent_entry)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	ASSERT_ANY_THROW(a.find(15));
}

TEST(OrderedTable, can_clear_table)
{
	OrderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	EXPECT_EQ(2, a.GetSize());

	a.clear();
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(true, a.empty());
}

TEST(OrderedTable, no_problem_when_clear_empty_table)
{
	OrderedTable<> a;
	ASSERT_NO_THROW(a.clear());
	EXPECT_EQ(0, a.GetSize());
}

/////////////////////////////////////////////////////////
TEST(HashTable, can_create_hash_table_by_constructor_of_default)
{
	ASSERT_NO_THROW(HashTable<> a);
}

TEST(HashTable, can_select_cells_in_the_vector_by_default)
{
	HashTable<> a;
	EXPECT_EQ(100, a.VectorSize());
}
TEST(HashTable, can_create_hash_table_by_constructor_of_copy_1)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(124, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(21, pol2);
	ASSERT_NO_THROW(HashTable<> b(a));
}

/*TEST(HashTable, can_create_hash_table_by_constructor_of_copy_2)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(124, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(21, pol2);
	ASSERT_NO_THROW(HashTable<> b(a));	
}*/

/*TEST(HashTable, can_create_hash_table_by_constructor_of_copy_3)
{
	UnorderedTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(124, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(21, pol2);
	ASSERT_NO_THROW(HashTable<> b(a));	
}*/

TEST(HashTable, can_insert_in_empty_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4");
	ASSERT_NO_THROW(a.insert(1, pol1));
}

TEST(HashTable, can_insert_in_non_empty_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4");
	ASSERT_NO_THROW(a.insert(42, pol2));
	EXPECT_EQ(2, a.GetSize());
}

TEST(HashTable, can_increase_the_size_of_the_table_when_there_are_many_elements)
{
	HashTable<> a; 
	EXPECT_EQ(100, a.VectorSize());
	
	Polynomial pol1("2x^3+4");
	for (int i = 0; i < 80; i++)
		a.insert(i, pol1);
	EXPECT_EQ(130, a.VectorSize());	//размер вектора увеличился, resize! 100*1.3

	for (int i = 81; i < 115; i++)
		a.insert(i, pol1);
	EXPECT_EQ(169, a.VectorSize()); //130*1.3
}

TEST(HashTable, throw_then_insert_with_index_existing_in_the_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4");
	ASSERT_ANY_THROW(a.insert(1, pol2));
}

TEST(HashTable, can_erase_element_from_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	ASSERT_NO_THROW(a.erase(1));
	EXPECT_EQ(1, a.GetSize());
}

TEST(HashTable, can_erase_last_element_from_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	a.erase(1);
	ASSERT_NO_THROW(a.erase(42));
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(true, a.empty());
	EXPECT_EQ(100, a.VectorSize());	//размер вектора списков пар всё равно останется равным ста и более (в программе никогда не уменьшается
}

TEST(HashTable, throw_when_erase_with_key_which_not_present_in_the_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	ASSERT_ANY_THROW(a.erase(2));
}

TEST(HashTable, can_find_in_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2); a.insert(34, pol2);
	Polynomial pol3("98y^2z^4+7xz-2x"); a.insert(23, pol3);
	EXPECT_EQ(pol2, a.find(34).second);
	EXPECT_EQ(4, a.GetSize());
}

TEST(HashTable, throw_when_search_for_a_non_existent_entry)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	ASSERT_ANY_THROW(a.find(15));
}

TEST(HashTable, can_clear_table)
{
	HashTable<> a;
	Polynomial pol1("2x^3+4"); a.insert(1, pol1);
	Polynomial pol2("-7y^12+xy^3-xz^25+4"); a.insert(42, pol2);
	EXPECT_EQ(2, a.GetSize());

	a.clear();
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(true, a.empty());
}

TEST(HashTable, no_problem_when_clear_empty_table)
{
	HashTable<> a;
	ASSERT_NO_THROW(a.clear());
	EXPECT_EQ(0, a.GetSize());
	EXPECT_EQ(100, a.VectorSize());
}