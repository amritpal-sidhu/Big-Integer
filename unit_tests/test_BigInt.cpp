#include <iostream>
#include <string>

#include "unity.h"

#include "BigInt.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::stringstream;


void setUp(void)
{
    
}

void tearDown(void)
{

}

void test_constructors(void)
{
    const size_t size = 4;
    // const string expected_buf[size] = {
    //     "8348428932819232918390812903812908",
    //     "-829103283628205018020001",
    //     "84289328192329183908120052334124",
    //     "-32987489127498082903829107482174892"
    // };
    BigInt actual;

    const int expected_default_int = 0;
    const BigInt default_con;
    TEST_ASSERT_EQUAL_STRING(to_string(expected_default_int).c_str(), default_con.to_str().c_str());

    const int expected_int_0 = -23423535;
    const BigInt integral_con(expected_int_0);
    TEST_ASSERT_EQUAL_STRING(to_string(expected_default_int).c_str(), default_con.to_str().c_str());

    const string expected_str = "-32987489127498082903829107482174892";
    const BigInt str_con(expected_str);
    actual = str_con;
    TEST_ASSERT_EQUAL_STRING(expected_str.c_str(), str_con.to_str().c_str());

    BigInt *ref = &actual;
    actual = *ref;
    TEST_ASSERT_EQUAL_STRING(ref->to_str().c_str(), actual.to_str().c_str());
}

void test_assignment_overloading(void)
{
    BigInt actual, expected_copy("-32987489127498082903829107482174892");
    const int expected_int = 230949;
    const string expected_str = "84289328192329183908120052334124";

    actual = expected_int;
    TEST_ASSERT_EQUAL_STRING(to_string(expected_int).c_str(), actual.to_str().c_str());

    actual = expected_str;
    TEST_ASSERT_EQUAL_STRING(expected_str.c_str(), actual.to_str().c_str());

    actual = expected_copy;
    TEST_ASSERT_EQUAL_STRING(expected_copy.to_str().c_str(), actual.to_str().c_str());

    BigInt *ref = &actual;
    actual = *ref;
    TEST_ASSERT_EQUAL_STRING(ref->to_str().c_str(), actual.to_str().c_str());
}

void test_comparison_overloading(void)
{
    const size_t size = 5;
    const string expected_lhs_buf[size] = {
        "8348428932819232918390812903812908",
        "-84289328192329183908120052334124",
        "84289328192329183908120052334124",
        "-329874891274980",
        "829103283628205018020001"
    };
    const string expected_rhs_buf[size] = {
        "14000601230105000540001",
        "-829103283628205018020001",
        "-5000000000100008750000",
        "-32987489127498082903829107482174892",
        "829103283628205018020001"
    };
    const size_t cmp_count = 6;
    /**
     * ==, !=, <, <=, >, >=
     */
    const bool expected_cmp[size][cmp_count] = {
        {false, true, false, false, true, true},
        {false, true, true, true, false, false},
        {false, true, false, false, true, true},
        {false, true, false, false, true, true},
        {true, false, false, true, false, true}
    };

    for (size_t i = 0; i < size; ++i) {
        BigInt lhs(expected_lhs_buf[i]);
        BigInt rhs(expected_rhs_buf[i]);

        TEST_ASSERT_EQUAL(lhs == rhs, expected_cmp[i][0]);
        TEST_ASSERT_EQUAL(lhs != rhs, expected_cmp[i][1]);
        TEST_ASSERT_EQUAL(lhs < rhs, expected_cmp[i][2]);
        TEST_ASSERT_EQUAL(lhs <= rhs, expected_cmp[i][3]);
        TEST_ASSERT_EQUAL(lhs > rhs, expected_cmp[i][4]);
        TEST_ASSERT_EQUAL(lhs >= rhs, expected_cmp[i][5]);
    }
}

void test_stream_overloading(void)
{
    stringstream is, os;
    BigInt actual_bi;
    const string expected[2] = {
        "8348428932819232918390812903812908",
        "-3"
    };

    is.str(expected[0]);
    is >> actual_bi;
    TEST_ASSERT_EQUAL_STRING(expected[0].c_str(), actual_bi.to_str().c_str());

    BigInt expected_bi(expected[1]);
    os << expected_bi;
    TEST_ASSERT_EQUAL_STRING(expected[1].c_str(), os.str().c_str());
}

/**
 * 
 * 
 */
void test_accumulation_overloading(void)
{

    BigInt actual("-22398237498237489273949223424");
    BigInt operand;
    const size_t size = 8-5;
    const string expected[size] = {
        "66830723283970822525867044053828931072", // multiply by -2983749203
        "66830723283970822433479545926330758178", // add -92387498127498172894
        "66830714000491010068588271035055938931", // subtract 9283479812364891274891274819247
        // "",
        // "",
        // "",
        // "",
        // ""
    };

    operand = "-2983749203";
    actual *= operand;
    TEST_ASSERT_EQUAL_STRING(expected[0].c_str(), actual.to_str().c_str());

    operand = "-92387498127498172894";
    actual += operand;
    TEST_ASSERT_EQUAL_STRING(expected[1].c_str(), actual.to_str().c_str());

    operand = "9283479812364891274891274819247";
    actual -= operand;
    TEST_ASSERT_EQUAL_STRING(expected[2].c_str(), actual.to_str().c_str());
}

void test_addition_with_two_operands(void)
{
    const size_t size = 4;
    BigInt operand1, operand2, actual;
    
    const string expected_buf[size] = {
        "14000601230105000540001",
        "-14000601230105018020001",
        "4000601229905000520001",
        "-4000601229905000520001"
    };

    const string op1_buf[size] = {
        "5000000000100000040000",
        "-5000000000100008750000",
        "9000601230005009270001",
        "-9000601230005009270001"
    };

    const string op2_buf[size] = {
        "9000601230005000500001",
        "-9000601230005009270001",
        "-5000000000100008750000",
        "5000000000100008750000"  
    };


    for (size_t i = 0; i < size; ++i) {
        operand1 = op1_buf[i];
        operand2 = op2_buf[i];
        actual = operand1 + operand2;

        TEST_ASSERT_EQUAL_STRING(expected_buf[i].c_str(), actual.to_str().c_str());
    }
}

void test_subtraction_with_two_operands(void)
{
    const size_t size = 4;
    BigInt operand1, operand2, actual;
    
    const string expected_buf[size] = {
        "999400000094999539999",
        "-999400000094999539999",
        "3000600000105000540001",
        "-3000600000105000540001"
    };

    const string op1_buf[size] = {
        "2000000000100000040000",
        "-2000000000100000040000",
        "2000000000100000040000",
        "-2000000000100000040000"
    };

    const string op2_buf[size] = {
        "1000600000005000500001",
        "-1000600000005000500001",
        "-1000600000005000500001",
        "1000600000005000500001"  
    };


    for (size_t i = 0; i < size; ++i) {
        operand1 = op1_buf[i];
        operand2 = op2_buf[i];
        actual = operand1 - operand2;

        TEST_ASSERT_EQUAL_STRING(expected_buf[i].c_str(), actual.to_str().c_str());
    }
}

void test_multiplication_with_two_operands(void)
{
    const size_t size = 4;
    BigInt operand1, operand2, actual;
    
    const string expected_buf[size] = {
        "136574764645336134277690592250000000000000000000",
        "136574764645336134277690592250000000000000000000",
        "-136574764645336134277690592250000000000000000000",
        "-136574764645336134277690592250000000000000000000"
    };

    const string op1_buf[size] = {
        "839228391910294000000000",
        "-839228391910294000000000",
        "839228391910294000000000",
        "-839228391910294000000000"
    };

    const string op2_buf[size] = {
        "162738494028375000000000",
        "-162738494028375000000000",
        "-162738494028375000000000",
        "162738494028375000000000"  
    };


    for (size_t i = 0; i < size; ++i) {
        operand1 = op1_buf[i];
        operand2 = op2_buf[i];
        actual = operand1 * operand2;

        TEST_ASSERT_EQUAL_STRING(expected_buf[i].c_str(), actual.to_str().c_str());
    }
}

void test_division_with_two_operands(void)
{
    const size_t size = 4;
    BigInt operand1, operand2, actual;
    
    const string expected_buf[size] = {
        "5",
        "5",
        "-5",
        "-5"
    };

    const string op1_buf[size] = {
        "839228391910294000000000",
        "-839228391910294000000000",
        "839228391910294000000000",
        "-839228391910294000000000"
    };

    const string op2_buf[size] = {
        "162738494028375000000000",
        "-162738494028375000000000",
        "-162738494028375000000000",
        "162738494028375000000000"  
    };


    for (size_t i = 0; i < size; ++i) {
        operand1 = op1_buf[i];
        operand2 = op2_buf[i];
        actual = operand1 / operand2;

        TEST_ASSERT_EQUAL_STRING(expected_buf[i].c_str(), actual.to_str().c_str());
    }
}
