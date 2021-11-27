#include "BigInt.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::stringstream;


// static void test_(void);
static void test_constructors(void);
static void test_assignment_overloading(void);
static void test_comparison_overloading(void);
static void test_stream_overloading(void);
static void test_accumulation_overloading(void);
static void test_addition_with_two_operands(void);
static void test_subtraction_with_two_operands(void);
static void test_multiplication_with_two_operands(void);
static void test_division_with_two_operands(void);

static bool ASSERT_EQUAL_STRING(const string &expected, const string &actual);
static void print_expected_and_actual(const string &expected, const string &actual);


int main()
{
    test_constructors();
    test_assignment_overloading();
    test_comparison_overloading();
    test_stream_overloading();   
    test_accumulation_overloading();
    test_addition_with_two_operands();
    test_subtraction_with_two_operands();
    test_multiplication_with_two_operands();
    // test_division_with_two_operands(); 

    return 0;
}


static void test_constructors(void)
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
    if (!ASSERT_EQUAL_STRING(to_string(expected_default_int), default_con.to_str())) {
        cout << "FAIL  1st test within test_constructors()\n";
        exit(134);
    }

    const int expected_int_0 = -23423535;
    const BigInt integral_con(expected_int_0);
    if (!ASSERT_EQUAL_STRING(to_string(expected_default_int), default_con.to_str())) {
        cout << "FAIL  2nd test within test_constructors()\n";
        exit(134);
    }

    const string expected_str = "-32987489127498082903829107482174892";
    const BigInt str_con(expected_str);
    actual = str_con;
    if (!ASSERT_EQUAL_STRING(expected_str, str_con.to_str())) {
        cout << "FAIL  3rd test within test_constructors()\n";
        exit(134);
    }

    BigInt *ref = &actual;
    actual = *ref;
    if (!ASSERT_EQUAL_STRING(ref->to_str(), actual.to_str())) {
        cout << "FAIL  4th test within test_constructors()\n";
        exit(134);
    }

    cout << "PASS  test_constructors()\n";
}

static void test_assignment_overloading(void)
{
    BigInt actual, expected_copy("-32987489127498082903829107482174892");
    const int expected_int = 230949;
    const string expected_str = "84289328192329183908120052334124";

    actual = expected_int;
    if (!ASSERT_EQUAL_STRING(to_string(expected_int), actual.to_str())) {
        cout << "FAIL  1st test within test_assignment_overloading()\n";
        exit(134);
    }

    actual = expected_str;
    if (!ASSERT_EQUAL_STRING(expected_str, actual.to_str())) {
        cout << "FAIL  2nd test within test_assignment_overloading()\n";
        exit(134);
    }

    actual = expected_copy;
    if (!ASSERT_EQUAL_STRING(expected_copy.to_str(), actual.to_str())) {
        cout << "FAIL  3rd test within test_assignment_overloading()\n";
        exit(134);
    }

    BigInt *ref = &actual;
    actual = *ref;
    if (!ASSERT_EQUAL_STRING(ref->to_str(), actual.to_str())) {
        cout << "FAIL  4th test within test_assignment_overloading()\n";
        exit(134);
    }

    cout << "PASS  test_assignment_overloading()\n";
}

static void test_comparison_overloading(void)
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

        if ((lhs == rhs) != expected_cmp[i][0]) {
            cout << "FAIL  == test within test_comparison_overloading() ";
            cout << "for batch " << i << endl;
            exit(134);
        }
        if ((lhs != rhs) != expected_cmp[i][1]) {
            cout << "FAIL  != test within test_comparison_overloading() ";
            cout << "for batch " << i << endl;
            exit(134);
        }
        if ((lhs < rhs) != expected_cmp[i][2]) {
            cout << "FAIL  < test within test_comparison_overloading() ";
            cout << "for batch " << i << endl;
            exit(134);
        }
        if ((lhs <= rhs) != expected_cmp[i][3]) {
            cout << "FAIL  <= test within test_comparison_overloading() ";
            cout << "for batch " << i << endl;
            exit(134);
        }
        if ((lhs > rhs) != expected_cmp[i][4]) {
            cout << "FAIL  > test within test_comparison_overloading() ";
            cout << "for batch " << i << endl;
            exit(134);
        }
        if ((lhs >= rhs) != expected_cmp[i][5]) {
            cout << "FAIL  >= test within test_comparison_overloading() ";
            cout << "for batch " << i << endl;
            exit(134);
        }
    }

    cout << "PASS  test_comparison_overloading()\n";
}

static void test_stream_overloading(void)
{
    stringstream is, os;
    BigInt actual_bi;
    const string expected[2] = {
        "8348428932819232918390812903812908",
        "-3"
    };

    is.str(expected[0]);
    is >> actual_bi;
    if (!ASSERT_EQUAL_STRING(expected[0], actual_bi.to_str())) {
        cout << "FAIL  1st test within test_stream_overloading()\n";
        exit(134);
    }

    BigInt expected_bi(expected[1]);
    os << expected_bi;
    if (!ASSERT_EQUAL_STRING(expected[1], os.str())) {
        cout << "FAIL  2nd test within test_stream_overloading()\n";
        exit(134);
    }

    cout << "PASS  test_stream_overloading()\n";
}

/**
 * 
 * 
 */
static void test_accumulation_overloading(void)
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
    if (!ASSERT_EQUAL_STRING(expected[0], actual.to_str())) {
        cout << "FAIL  1st test within test_accumulation_overloading()\n";
        exit(134);
    }

    operand = "-92387498127498172894";
    actual += operand;
    if (!ASSERT_EQUAL_STRING(expected[1], actual.to_str())) {
        cout << "FAIL  2nd test within test_accumulation_overloading()\n";
        exit(134);
    }

    operand = "9283479812364891274891274819247";
    actual -= operand;
    if (!ASSERT_EQUAL_STRING(expected[2], actual.to_str())) {
        cout << "FAIL  3rd test within test_accumulation_overloading()\n";
        exit(134);
    }

    cout << "PASS  test_accumulation_overloading()\n";
}

static void test_addition_with_two_operands(void)
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

        if (!ASSERT_EQUAL_STRING(expected_buf[i], actual.to_str())) {
            cout << "FAIL  1st test within test_addition_with_two_operands()\n";
            exit(134);
        }
    }

    cout << "PASS  test_addition_with_two_operands()\n";
}

static void test_subtraction_with_two_operands(void)
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

        if (!ASSERT_EQUAL_STRING(expected_buf[i], actual.to_str())) {
            cout << "FAIL  1st test within test_subtraction_with_two_operands()\n";
            print_expected_and_actual(operand1.to_str(), operand2.to_str());
            print_expected_and_actual(expected_buf[i], actual.to_str());
            exit(134);
        }
    }

    cout << "PASS  test_subtraction_with_two_operands()\n";
}

static void test_multiplication_with_two_operands(void)
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

        if (!ASSERT_EQUAL_STRING(expected_buf[i], actual.to_str())) {
            cout << "FAIL  1st test within test_multiplication_with_two_operands()\n";
            exit(134);
        }
    }

    cout << "PASS  test_multiplication_with_two_operands()\n";
}

static void test_division_with_two_operands(void)
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

        if (!ASSERT_EQUAL_STRING(expected_buf[i], actual.to_str())) {
            cout << "FAIL  1st test within test_division_with_two_operands()\n";
            exit(134);
        }
    }

    cout << "PASS  test_division_with_two_operands()\n";
}

static bool ASSERT_EQUAL_STRING(const string &expected, const string &actual)
{
    return (expected.compare(actual) == 0);
}

static void print_expected_and_actual(const string &expected, const string &actual)
{
    cout << "Expected: " << expected << ", Actual: " << actual << endl;
}
