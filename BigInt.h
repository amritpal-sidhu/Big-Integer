/**
 *  @summary This header defines a big integer class BigInt.  It allows for
 *           the use of integers that cannot be represented by 64 bits.
 *
 *           This particular implementation uses a vector, where each element
 *           can be thought of a a digit of a number system with a large base.
 *           TODO: Optimal base needs to be experimented with to determine
 *           what provides best performance.
 *
 *  @author Amritpal Sidhu
 *  @modified 2020-12-26
 */
#include <vector>
#include <iomanip>
//#include <iostream>

/**
 *  @brief Base choice considerations:
 *           - Multiple of 10 for easy conversion to base 10
 *           - (base-1)^2 can fit in a long long data type
 *
 *         Current base is 10^9
 */
#define BASE  1000000000
#define DIGITS_IN_BASE10  9

#define POS  true
#define NEG  false

class BigInt {
public:
    BigInt();
    BigInt(const long long&);
    BigInt(const std::string&);
    BigInt(const BigInt&);  // copy constructor
    ~BigInt();

    /* Assignment operators */
    BigInt& operator=(const long long&);
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

private:
    std::vector<long long> bigDigits;
    bool sign;

    /* Utility function */
    BigInt addMag(const BigInt&, const BigInt&) const;
    BigInt subMag(BigInt, BigInt) const;
    int compareMag(const BigInt&, const BigInt&) const;
    void stringToBigInt(const std::string&);
};
