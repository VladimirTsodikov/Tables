#pragma once
#include "Polynomial.h"
#include <gtest.h>

TEST(Polynomial, can_create_polynomial_by_constructor_of_default)
{
	ASSERT_NO_THROW(Polynomial a);
}

TEST(Polynomial, can_create_polynomial_by_constructor_with_parametrs)
{
	ASSERT_NO_THROW(Polynomial a("12x+5"));
}

TEST(Polynomial, can_create_polynomial_by_constructor_of_copy)
{
	Polynomial a("43x^2y-35z");
	ASSERT_NO_THROW(Polynomial b(a));
}

TEST(Polynomial, throw_then_negative_degree)
{
	ASSERT_ANY_THROW(Polynomial a("12x^-4+5"));
}

TEST(Polynomial, throw_then_too_large_degree)
{
	ASSERT_ANY_THROW(Polynomial a("12xyz^1024+5"));
}

TEST(Polynomial, operator_of_equal_is_correctly)
{
	Polynomial a("43x^2y-35z");
	Polynomial b("12x+5");
	ASSERT_NO_THROW(b = a);
	EXPECT_EQ(b, a);
}

TEST(Polynomial, operator_of_doudle_equal_is_correctly)	
{
	Polynomial a("43x^2y-35z");
	Polynomial b("-35z+24+43x^2y-24");
	EXPECT_EQ(true, a==b);
}

TEST(Polynomial, operator_of__not_equal_is_correct)
{
	Polynomial a("43x^2y-35z");
	Polynomial b("-35z+24");
	EXPECT_EQ(true, a != b);
}

TEST(Polynomial, can_delete_monomial_with_zero_coefficients)
{
	Polynomial a("15xyz-23y+4"), b("-4");
	EXPECT_EQ(3, a.GetCount());
	a += b;	//15xyz-23y
	EXPECT_EQ(2, a.GetCount());
}

TEST(Polynomial, can_to_group_monomials_with_the_same_coefficients)
{
	Polynomial a("15xyz-23y+4"), b("12xyz");
	EXPECT_EQ(3, a.GetCount());
	a += b;	//27xyz-23y+4
	EXPECT_EQ(3, a.GetCount());	
}

TEST(Polynomial, can_AddEq_correctly)
{
	Polynomial a("32x^4yz^5"), b("x^7+12y"), c("x^7+32x^4yz^5+12y");
	a += b;
	EXPECT_EQ(c, a);
}

TEST(Polynomial, can_Add_correctly)
{
	Polynomial a("32x^4yz^5"), b("x^7+12y"), c("x^7+32x^4yz^5+12y"), d;
	d = a + b;
	EXPECT_EQ(c, d);
}

TEST(Polynomial, can_SubEq_correctly)
{
	Polynomial a("32x^4yz^5"), b("x^7+12y"), c("-x^7+32x^4yz^5-12y");
	a -= b;
	EXPECT_EQ(c, a);
}

TEST(Polynomial, can_Sub_correctly)
{
	Polynomial a("32x^4yz^5"), b("x^7+12y"), c("-x^7+32x^4yz^5-12y"), d;
	d = a - b;
	EXPECT_EQ(c, d);
}

TEST(Polynomial, can_MultEq_Pol_and_Pol_correctly)
{
	Polynomial a("x^2+y"), b("7x+z"), c("7x^3+x^2z+7xy+yz");
	a *= b;
	EXPECT_EQ(c, a);
}

TEST(Polynomial, can_Mult_Pol_and_Pol_correctly)
{
	Polynomial a("x^2+y"), b("7x+z"), c("7x^3+x^2z+7xy+yz"), d;
	d = a * b;
	EXPECT_EQ(c, d);
}

TEST(Polynomial, throw_when_too_large_degree_after_Mult)
{
	Polynomial a("xy^1020"), b("-4xy^13"), c;
	ASSERT_ANY_THROW(c = a * b);
}

TEST(Polynomial, can_MultEq_Pol_and_Scalar_correctly)
{
	Polynomial a("x^2y^109+y^65z+12"), b("7x^2y^109+7y^65z+84");
	a *= 7;
	EXPECT_EQ(b, a);
}

TEST(Polynomial, can_Mult_Pol_and_Scalar_correctly)
{
	Polynomial a("x^2y^109+y^65z+12"), b("7x^2y^109+7y^65z+84"), c;
	c = a * 7;
	EXPECT_EQ(b, c);
}

TEST(Polynomial, can_Add_when_input_Pol_is_empty)
{
	Polynomial a("x^2y^109+y^65z+12"), b, c;
	ASSERT_NO_THROW(c = a+b);
	EXPECT_EQ(a, c);
}

TEST(Polynomial, can_Mult_when_input_Pol_is_empty)
{
	Polynomial a("x^2y^109+y^65z+12"), b;
	ASSERT_NO_THROW(a *= b);
	EXPECT_EQ(true, a.empty());
}

TEST(Polynomial, function_empty_is_correct)
{
	Polynomial a("12x+5"), b("-5-12x^1"), c;
	EXPECT_EQ(false, a.empty());
	a += b;
	EXPECT_EQ(true, a.empty());
	EXPECT_EQ(true, c.empty());
}

TEST(Polynomial, function_clear_is_correct)
{
	Polynomial a("12y-4");
	EXPECT_EQ(false, a.empty());
	a.clear();
	EXPECT_EQ(true, a.empty());
}

TEST(Polynomial, can_clear_empty_Pol)
{
	Polynomial a;
	ASSERT_NO_THROW(a.clear());
}