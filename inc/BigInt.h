/**
 *  This header defines a big integer class BigInt.  It allows for
 *  the use of integers that cannot be represented by 64 bits.
 *
 *  This particular implementation uses a vector, where each element
 *  can be thought of a a digit of a number system with a large base.
 *
 *  @author Amritpal Sidhu
 *  @created 2020-12-26
 */
#ifndef __BIGINT
#define __BIGINT

#include <vector>
#include <iomanip>



class BigInt {
private:
    /**
     *  Base choice considerations:
     *    - Multiple of 10 for easy conversion to base 10
     *    - (base-1)^2 can fit in a digit_t data type
     *
     * Current base is 10^9
     */
    typedef long long digit_t;
    typedef unsigned long long u_digit_t;
    static const size_t BIG_DIGIT_SIZE = 9;
    static const u_digit_t BASE = 1E9;

public:
    BigInt();
    BigInt(const digit_t&);
    BigInt(const std::string&);
    BigInt(const BigInt&);  // copy constructor
    ~BigInt();

    /* Assignment operators */
    BigInt& operator=(const digit_t&);
    BigInt& operator=(const std::string&);
    BigInt& operator=(const BigInt&);  // copy assignment

    /* Arithmetic operators */
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;

    void operator+=(const BigInt&);
    void operator-=(const BigInt&);
    void operator*=(const BigInt&);
    void operator/=(const BigInt&);

    /* Comparison operators */
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    /* I/O stream operators */
    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    /* Metadata */
    size_t size(void) const;
    std::string to_str(void) const;

private:
    enum sign_e {NEG,POS} sign;
    std::vector<u_digit_t> digits;

    /* Helper functions */
    void string_to_BigInt(const std::string&);
    void remove_leading_zeros(void);
    void borrow(const size_t);
    void sum(const BigInt&);
    void sum(const std::vector<u_digit_t>&);
    void dif(BigInt);
    
    static BigInt sum(const BigInt&, const BigInt&);
    static BigInt dif(BigInt, BigInt);
    static size_t max_size(const BigInt&, const BigInt&);
    static int compare_magnitude(const BigInt&, const BigInt&);
};

#endif /* __BIGINT */
