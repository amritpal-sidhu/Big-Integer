#include "BigInt.h"

BigInt::BigInt() {

    bigDigits.push_back(0);
    sign = POS;
}

BigInt::BigInt(const long long& initialVal) {

    if (initialVal < 0) {
        sign = NEG;
        bigDigits.push_back(-initialVal);
    }
    else {
        sign = POS;
        bigDigits.push_back(initialVal);
    }
}

BigInt::BigInt(const std::string& initialVal) {

    stringToBigInt(initialVal);
}

BigInt::BigInt(const BigInt& b) {

    bigDigits = b.bigDigits;
    sign = b.sign;
}

BigInt::~BigInt() {

    bigDigits.clear();
    sign = POS;
}

BigInt& BigInt::operator=(const long long& rhs) {

    bigDigits.clear();

    if (rhs < 0) {
        sign = NEG;
        bigDigits.push_back(-rhs);
    }
    else {
        sign = POS;
        bigDigits.push_back(rhs);
    }

    return *this;
}

BigInt& BigInt::operator=(const std::string& rhs) {

    stringToBigInt(rhs);

    return *this;
}

BigInt& BigInt::operator=(const BigInt& rhs) {

    if (this == &rhs)
        return *this;

    bigDigits.clear();
    bigDigits = rhs.bigDigits;
    sign = rhs.sign;

    return *this;
}

BigInt BigInt::operator+(const BigInt& rhs) const {

    BigInt result;

    if (sign == rhs.sign) {

        result = addMag(*this, rhs);
        result.sign = sign;
    }
    else {

        if (sign == POS)
            result = subMag(*this, rhs);
        else
            result = subMag(rhs, *this);
    }

    return result;
}

BigInt BigInt::operator-(const BigInt& rhs) const {

    BigInt result;

    if (sign == rhs.sign) {

        if (sign == POS)
            result = subMag(*this, rhs);
        else
            result = subMag(rhs, *this);
    }
    else {

        result = addMag(*this, rhs);

        if (sign == POS && rhs.sign == NEG)
            result.sign = POS;
        else
            result.sign = NEG;
    }

    return result;
}

BigInt BigInt::operator*(const BigInt& rhs) const {

    BigInt result;
    BigInt products;
    long long product, carry;

    for (size_t i=0; i<bigDigits.size(); i++) {

        carry = 0;
        products.bigDigits.clear();
        for (size_t k=0; k<i; k++)
            products.bigDigits.push_back(0);

        for (size_t j=0; j<rhs.bigDigits.size(); j++) {

            product = (bigDigits[i] * rhs.bigDigits[j] + carry)%BASE;
            carry = (bigDigits[i] * rhs.bigDigits[j] + carry)/BASE;
            products.bigDigits.push_back(product);
        }

        if (carry > 0)
            products.bigDigits.push_back(carry);

        result = addMag(result, products);
    }

    if (sign == rhs.sign)
        result.sign = POS;
    else
        result.sign = NEG;

    return result;
}

BigInt BigInt::operator/(const BigInt& rhs) const {

    BigInt result;

    result = rhs; // temporary

    return result;
}

void BigInt::operator+=(const BigInt& rhs) {

    *this = *this + rhs;
}

void BigInt::operator-=(const BigInt& rhs) {

    *this = *this - rhs;
}

void BigInt::operator*=(const BigInt& rhs) {

    *this = *this * rhs;
}

void BigInt::operator/=(const BigInt& rhs) {

    *this = *this / rhs;
}

bool BigInt::operator==(const BigInt& rhs) const {

    if (sign != rhs.sign)
        return false;

    if (bigDigits.size() != rhs.bigDigits.size())
        return false;

    for (size_t i=0; i<bigDigits.size(); i++) {

        if (bigDigits[i] != rhs.bigDigits[i])
            return false;
    }

    return true;
}

bool BigInt::operator!=(const BigInt& rhs) const {

    if (sign != rhs.sign)
        return true;

    if (bigDigits.size() != rhs.bigDigits.size())
        return true;

    for (size_t i=0; i<bigDigits.size(); i++) {

        if (bigDigits[i] != rhs.bigDigits[i])
            return true;
    }

    return false;
}

bool BigInt::operator<(const BigInt& rhs) const {

    if (sign == POS && rhs.sign == NEG)
        return false;

    if (sign == NEG && rhs.sign == POS)
        return true;

    if (bigDigits.size() != rhs.bigDigits.size())
        return bigDigits.size() < rhs.bigDigits.size() ? true : false;

    if (sign == POS) {

        if (compareMag(*this, rhs) < 0)
            return true;

        return false;
    }

    // case where both numbers are negative
    if (compareMag(*this, rhs) > 0)
        return true;

    return false;
}

bool BigInt::operator<=(const BigInt& rhs) const {

    if (sign == POS && rhs.sign == NEG)
        return false;

    if (sign == NEG && rhs.sign == POS)
        return true;

    if (bigDigits.size() != rhs.bigDigits.size())
        return bigDigits.size() < rhs.bigDigits.size() ? true : false;

    if (sign == POS) {

        if (compareMag(*this, rhs) <= 0)
            return true;

        return false;
    }

    // case where both numbers are negative
    if (compareMag(*this, rhs) >= 0)
        return true;

    return false;
}

bool BigInt::operator>(const BigInt& rhs) const {

    if (sign == POS && rhs.sign == NEG)
        return true;

    if (sign == NEG && rhs.sign == POS)
        return false;

    if (bigDigits.size() != rhs.bigDigits.size())
        return bigDigits.size() > rhs.bigDigits.size() ? true : false;

    if (sign == POS) {

        if (compareMag(*this, rhs) > 0)
            return true;

        return false;
    }

    // case where both numbers are negative
    if (compareMag(*this, rhs) < 0)
        return true;

    return false;
}

bool BigInt::operator>=(const BigInt& rhs) const {

    if (sign == POS && rhs.sign == NEG)
        return true;

    if (sign == NEG && rhs.sign == POS)
        return false;

    if (bigDigits.size() != rhs.bigDigits.size())
        return bigDigits.size() > rhs.bigDigits.size() ? true : false;

    if (sign == POS) {

        if (compareMag(*this, rhs) >= 0)
            return true;

        return false;
    }

    // case where both numbers are negative
    if (compareMag(*this, rhs) <= 0)
        return true;

    return false;
}

std::istream& operator>>(std::istream& is, BigInt& rhs) {

    std::string input;

    is >> input;

    size_t lastIndex;
    size_t i = input.length()-1;

    if (input[0] == '-') {
        rhs.sign = NEG;
        lastIndex = 1;
    }
    else {
        rhs.sign = POS;
        lastIndex = 0;
    }

    rhs.bigDigits.clear();

    while (i >= lastIndex) {

        if (i-lastIndex+1 < DIGITS_IN_BASE10) {

            rhs.bigDigits.push_back(
                std::stoi(input.substr(lastIndex, i-lastIndex+1)));
            break;
        }
        else {

            rhs.bigDigits.push_back(
                std::stoi(
                    input.substr(i-DIGITS_IN_BASE10+1, DIGITS_IN_BASE10)));
            i -= DIGITS_IN_BASE10;
        }
    }

    for (int i=rhs.bigDigits.size()-1; rhs.bigDigits[i] == 0; i--) {
        rhs.bigDigits.erase(rhs.bigDigits.end()-1);
    }

    if (rhs.bigDigits.empty())
        rhs.bigDigits.push_back(0);

    return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& rhs) {

    int i = rhs.bigDigits.size()-1;

    if (i < 0) {
        os << "";
    }
    else {

        if (rhs.sign == NEG)
            os << "-";

        os << rhs.bigDigits[i--];

        while (i >= 0) {
            os << std::setfill('0');
            os << std::setw(DIGITS_IN_BASE10);
            os << rhs.bigDigits[i--];
        }
    }

    return os;
}

BigInt BigInt::addMag(const BigInt& a, const BigInt& b) const {

    BigInt result;
    long long sum, carry=0;

    result.bigDigits.clear();

    if (a.bigDigits.size() > b.bigDigits.size()) {

        for (size_t i=0; i<a.bigDigits.size(); i++) {

            if (i > b.bigDigits.size()-1) {

                sum = (a.bigDigits[i] + carry)%BASE;
                carry = (a.bigDigits[i] + carry)/BASE;
            }
            else {

                sum = (a.bigDigits[i] + b.bigDigits[i] + carry)%BASE;
                carry = (a.bigDigits[i] + b.bigDigits[i] + carry)/BASE;
            }

            result.bigDigits.push_back(sum);
        }
    }
    else {

        for (size_t i=0; i<b.bigDigits.size(); i++) {

            if (i > a.bigDigits.size()-1) {

                sum = (b.bigDigits[i] + carry)%BASE;
                carry = (b.bigDigits[i] + carry)/BASE;
            }
            else {

                sum = (a.bigDigits[i] + b.bigDigits[i] + carry)%BASE;
                carry = (a.bigDigits[i] + b.bigDigits[i] + carry)/BASE;
            }

            result.bigDigits.push_back(sum);
        }
    }

    if (carry > 0)
        result.bigDigits.push_back(carry);

    return result;
}

/**
 *  @brief  Performs a - b. This function ignores the signs of the parameters.
 *
 *          Follow below examples for how to call this function based on the
 *          sign of each argument.
 *              For (+x) - (+y) call as sub(x, y)
 *              For (-x) - (-y) call as sub(y, x)
 *              For (+x) + (-y) call as sub(x, y)
 *              For (-x) + (+y) call as sub(y, x)
 */
BigInt BigInt::subMag(BigInt a, BigInt b) const {

    BigInt result;

    if (a.bigDigits.size() == b.bigDigits.size()) {

        int compare = compareMag(a, b);

        if (compare == 0)
            return result;

        result.bigDigits.clear();

        if (compare > 0) {

            result.sign = POS;

            for (size_t i=0; i<a.bigDigits.size(); i++) {

                if (a.bigDigits[i] < b.bigDigits[i]) {

                    size_t borrow = i+1;
                    while (a.bigDigits[borrow] < 1)
                        borrow++;
                    a.bigDigits[borrow--] -= 1;
                    while (borrow != i)
                        a.bigDigits[borrow--] = BASE-1;

                    result.bigDigits.push_back(
                        (a.bigDigits[i]+BASE)-b.bigDigits[i]);
                }
                else {

                    result.bigDigits.push_back(a.bigDigits[i]-b.bigDigits[i]);
                }
            }
        }
        else {

            result.sign = NEG;

            for (size_t i=0; i<a.bigDigits.size(); i++) {

                if (b.bigDigits[i] < a.bigDigits[i]) {

                    size_t borrow = i+1;
                    while (b.bigDigits[borrow] < 1)
                        borrow++;
                    b.bigDigits[borrow--] -= 1;
                    while (borrow != i)
                        b.bigDigits[borrow--] = BASE-1;

                    result.bigDigits.push_back(
                        (b.bigDigits[i]+BASE)-a.bigDigits[i]);
                }
                else {

                    result.bigDigits.push_back(b.bigDigits[i]-a.bigDigits[i]);
                }
            }
        }
    }
    else if (a.bigDigits.size() > b.bigDigits.size()) {

        result.bigDigits.clear();
        result.sign = POS;

        for (size_t i=0; i<a.bigDigits.size(); i++) {

            if (i > b.bigDigits.size()-1) {

                result.bigDigits.push_back(a.bigDigits[i]);
            }
            else {

                if (a.bigDigits[i] < b.bigDigits[i]) {

                    size_t borrow = i+1;
                    while (a.bigDigits[borrow] < 1)
                        borrow++;
                    a.bigDigits[borrow--] -= 1;
                    while (borrow != i)
                        a.bigDigits[borrow--] = BASE-1;

                    result.bigDigits.push_back(
                        (a.bigDigits[i]+BASE)-b.bigDigits[i]);
                }
                else {

                    result.bigDigits.push_back(a.bigDigits[i]-b.bigDigits[i]);
                }
            }
        }
    }
    else {

        result.bigDigits.clear();
        result.sign = NEG;

        for (size_t i=0; i<b.bigDigits.size(); i++) {

            if (i > a.bigDigits.size()-1) {

                result.bigDigits.push_back(b.bigDigits[i]);
            }
            else {

                if (b.bigDigits[i] < a.bigDigits[i]) {

                    size_t borrow = i+1;
                    while (b.bigDigits[borrow] < 1)
                        borrow++;
                    b.bigDigits[borrow--] -= 1;
                    while (borrow != i)
                        b.bigDigits[borrow--] = BASE-1;

                    result.bigDigits.push_back(
                        (b.bigDigits[i]+BASE)-a.bigDigits[i]);
                }
                else {

                    result.bigDigits.push_back(b.bigDigits[i]-a.bigDigits[i]);
                }
            }
        }
    }

    for (int i=result.bigDigits.size()-1; result.bigDigits[i] == 0; i--) {
        result.bigDigits.erase(result.bigDigits.end()-1);
    }

    return result;
}

/**
 *  @brief  Compares the magnitude of two BigInt types when they have
 *          the same number of digits.
 *  @retval  0 if a == b
 *           1 if a > b
 *          -1 if a < b
 */
int BigInt::compareMag(const BigInt& a, const BigInt& b) const {

    int result = 0;

    for (int i=a.bigDigits.size()-1; i>=0; i--) {

        if (a.bigDigits[i] > b.bigDigits[i]) {
            result = 1;
            break;
        }
        else if (a.bigDigits[i] < b.bigDigits[i]) {
            result = -1;
            break;
        }
    }

    return result;
}

void BigInt::stringToBigInt(const std::string& s) {

    size_t lastIndex;
    size_t i = s.length()-1;

    if (s[0] == '-') {
        sign = NEG;
        lastIndex = 1;
    }
    else {
        sign = POS;
        lastIndex = 0;
    }

    bigDigits.clear();

    while (i >= lastIndex) {

        if (i-lastIndex+1 < DIGITS_IN_BASE10) {

            bigDigits.push_back(
                std::stoi(s.substr(lastIndex, i-lastIndex+1)));
            break;
        }
        else {

            bigDigits.push_back(
                std::stoi(s.substr(i-DIGITS_IN_BASE10+1, DIGITS_IN_BASE10)));
            i -= DIGITS_IN_BASE10;
        }
    }

    for (int i=bigDigits.size()-1; bigDigits[i] == 0; i--) {
        bigDigits.erase(bigDigits.end()-1);
    }

    if (bigDigits.empty())
        bigDigits.push_back(0);
}
