#include "BigInt.h"

#include <iostream>



BigInt::BigInt()
{
    this->digits.clear();
    this->digits.push_back(0);
    this->sign = POS;
}

BigInt::BigInt(const digit_t& initial_value)
{
    this->digits.clear();

    if (initial_value < 0) {
        this->sign = NEG;
        this->digits.push_back(-initial_value);
    }
    else {
        this->sign = POS;
        this->digits.push_back(initial_value);
    }
}

BigInt::BigInt(const std::string& initial_value)
{
    this->digits.clear();
    this->string_to_BigInt(initial_value);
}

BigInt::BigInt(const BigInt& bi)
{
    this->digits.clear();
    this->digits = bi.digits;
    this->sign = bi.sign;
}

BigInt::~BigInt()
{
    this->digits.clear();
    this->sign = POS;
}

BigInt& BigInt::operator=(const digit_t& rhs)
{
    this->digits.clear();

    if (rhs < 0) {
        this->sign = NEG;
        this->digits.push_back(-rhs);
    }
    else {
        this->sign = POS;
        this->digits.push_back(rhs);
    }

    return *this;
}

BigInt& BigInt::operator=(const std::string& rhs)
{
    this->digits.clear();
    this->string_to_BigInt(rhs);
    return *this;
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this != &rhs) {
        this->digits.clear();
        this->digits = rhs.digits;
        this->sign = rhs.sign;
    }

    return *this;
}

BigInt BigInt::operator+(const BigInt& rhs) const
{
    BigInt result;

    if (this->sign == rhs.sign) {
        result = sum(*this, rhs);
        result.sign = this->sign;
    }
    else
        result = (this->sign == POS) ? dif(*this, rhs) : dif(rhs, *this);

    return result;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
    BigInt result;

    if (this->sign != rhs.sign) {
        result = sum(*this, rhs);
        result.sign = (this->sign == POS && rhs.sign == NEG) ? POS : NEG;
    }
    else
        result = (this->sign == POS) ? dif(*this, rhs) : dif(rhs, *this);

    return result;
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    BigInt result;
    std::vector<u_digit_t> products;
    u_digit_t product, carry;

    for (size_t i = 0; i < this->size(); ++i) {

        carry = 0;
        products.clear();

        for (size_t k = 0; k < i; ++k)
            products.push_back(0);

        for (size_t j = 0; j < rhs.size(); ++j) {
            product = (this->digits[i] * rhs.digits[j] + carry)%BASE;
            carry = (this->digits[i] * rhs.digits[j] + carry)/BASE;
            products.push_back(product);
        }

        if (carry > 0) products.push_back(carry);

        result.sum(products);
    }

    result.sign = (this->sign == rhs.sign) ? POS : NEG;

    return result;
}

BigInt BigInt::operator/(const BigInt& rhs) const
{
    BigInt result;

    result = rhs; // temporary

    return result;
}

void BigInt::operator+=(const BigInt& rhs)
{
    if (this->sign == rhs.sign)
        this->sum(rhs);
    else if (this->sign == POS)
        this->dif(rhs);
    else
        *this = dif(rhs, *this);
}

void BigInt::operator-=(const BigInt& rhs)
{
    if (this->sign != rhs.sign)
        this->sum(rhs);
    else if (this->sign == POS)
        this->dif(rhs);
    else
        *this = dif(rhs, *this);
}

void BigInt::operator*=(const BigInt& rhs)
{
    std::vector<u_digit_t> products;
    u_digit_t product, carry;

    for (size_t i = 0; i < this->size(); ++i) {

        carry = 0;
        products.clear();

        for (size_t k = 0; k < i; ++k)
            products.push_back(0);

        for (size_t j = 0; j < rhs.size(); ++j) {
            product = (this->digits[i] * rhs.digits[j] + carry)%BASE;
            carry = (this->digits[i] * rhs.digits[j] + carry)/BASE;
            products.push_back(product);
        }

        if (carry > 0) products.push_back(carry);

        this->sum(products);
    }

    this->sign = (this->sign == rhs.sign) ? POS : NEG;
}

void BigInt::operator/=(const BigInt& rhs)
{
    *this = *this / rhs;
}

bool BigInt::operator==(const BigInt& rhs) const
{
    return (this->sign == rhs.sign && !compare_magnitude(*this, rhs));
}

bool BigInt::operator!=(const BigInt& rhs) const
{
    return (this->sign != rhs.sign || compare_magnitude(*this, rhs));
}

bool BigInt::operator<(const BigInt& rhs) const
{
    const bool sign_check = (this->sign == NEG && rhs.sign == POS);
    const bool pos_mag_check = (this->sign == rhs.sign && this->sign == POS && compare_magnitude(*this, rhs) < 0);
    const bool neg_mag_check = (this->sign == rhs.sign && this->sign == NEG && compare_magnitude(*this, rhs) > 0);

    return sign_check || pos_mag_check || neg_mag_check;
}

bool BigInt::operator<=(const BigInt& rhs) const
{
    const bool sign_check = (this->sign == NEG && rhs.sign == POS);
    const bool pos_mag_check = (this->sign == rhs.sign && this->sign == POS && compare_magnitude(*this, rhs) <= 0);
    const bool neg_mag_check = (this->sign == rhs.sign && this->sign == NEG && compare_magnitude(*this, rhs) >= 0);

    return sign_check || pos_mag_check || neg_mag_check;
}

bool BigInt::operator>(const BigInt& rhs) const
{
    const bool sign_check = (this->sign == POS && rhs.sign == NEG);
    const bool pos_mag_check = (this->sign == rhs.sign && this->sign == POS && compare_magnitude(*this, rhs) > 0);
    const bool neg_mag_check = (this->sign == rhs.sign && this->sign == NEG && compare_magnitude(*this, rhs) < 0);

    return sign_check || pos_mag_check || neg_mag_check;
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    const bool sign_check = (this->sign == POS && rhs.sign == NEG);
    const bool pos_mag_check = (this->sign == rhs.sign && this->sign == POS && compare_magnitude(*this, rhs) >= 0);
    const bool neg_mag_check = (this->sign == rhs.sign && this->sign == NEG && compare_magnitude(*this, rhs) <= 0);

    return sign_check || pos_mag_check || neg_mag_check;
}

std::istream& operator>>(std::istream& is, BigInt& rhs)
{
    std::string input;

    is >> input;
    rhs.digits.clear();
    rhs.string_to_BigInt(input);

    return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& rhs)
{
    if (rhs.size() != 0)
        os << rhs.to_str();

    return os;
}

size_t BigInt::size(void) const
{
    return this->digits.size();
}

std::string BigInt::to_str(void) const
{
    std::string result;

    if (this->size() > 0) {
        for (size_t i = 0; i < this->size()-1; ++i) {
            std::string temp_str = std::to_string(this->digits[i]);
            if (temp_str.size() < BIG_DIGIT_SIZE)
                temp_str.insert(0, BIG_DIGIT_SIZE-temp_str.size(), '0');
            result.insert(0, temp_str);
        }

        result.insert(0, std::to_string(this->digits[this->size()-1]));
        if (this->sign == NEG) result.insert(0, 1, '-');
    }
    
    return result;
}

void BigInt::string_to_BigInt(const std::string& s)
{
    size_t msd_index = 0;
    size_t i = s.size()-1;

    this->sign = POS;    

    if (s[msd_index] == '-') {
        this->sign = NEG;
        msd_index = 1;
    }

    try {

        for (size_t ii = msd_index; ii <= i; ++ii) {
            if (!isdigit(s[ii])) {
                this->sign = POS;
                std::string error_message;
                error_message += "ERROR: ";
                error_message += s[ii];
                error_message += " is not a number";
                throw error_message;
            }
        }

        while (i >= msd_index) {
            const size_t remaining_chars = i-msd_index+1;

            if (remaining_chars <= BIG_DIGIT_SIZE) {
                std::string temp_str = s.substr(msd_index, remaining_chars);
                this->digits.push_back(strtoull(temp_str.c_str(), NULL, 10));
                break;
            }
            else {
                std::string temp_str = s.substr(i-BIG_DIGIT_SIZE+1, BIG_DIGIT_SIZE);
                this->digits.push_back(strtoull(temp_str.c_str(), NULL, 10));
                i -= BIG_DIGIT_SIZE;
            }
        }

        this->remove_leading_zeros();
        
        if (this->digits.empty()) this->digits.push_back(0);

    } catch (const std::string &e) {
        std::cout << e << std::endl;
    }
}

void BigInt::remove_leading_zeros(void)
{
    for (size_t i = this->size()-1; i > 0 && this->digits[i] == 0; --i) {
        this->digits.pop_back();
    }
}

/**
 * Modifies digits such that BASE is borrowed at
 * the borrow_index.
 * 
 * Used for subtracting
 */
void BigInt::borrow(const size_t borrow_index)
{
    size_t i = borrow_index + 1;
    while (this->digits[i] == 0) ++i;
    this->digits[i--] -= 1;
    while (i != borrow_index) this->digits[i--] = BASE-1;
    this->digits[borrow_index] += BASE;
}

void BigInt::sum(const BigInt& rhs)
{
    this->sum(rhs.digits);
}

/**
 * Used for multiplication
 */
void BigInt::sum(const std::vector<u_digit_t>& vec)
{
    const size_t max_digits = this->size() > vec.size() ? this->size() : vec.size();
    u_digit_t sum, carry = 0, temp;

    for (size_t i = 0; i < max_digits; ++i) {

        if (i >= vec.size())
            temp = this->digits[i] + carry;
        else if (i >= this->size())
            temp = vec[i] + carry;
        else
            temp = this->digits[i] + vec[i] + carry;

        sum = temp % BASE;
        carry = temp / BASE;

        if (i >= this->size())
            this->digits.push_back(sum);
        else
            this->digits[i] = sum;
    }

    if (carry > 0) this->digits.push_back(carry);
}

/**
 * Computes thet difference between this and rhs
 */
void BigInt::dif(BigInt rhs)
{
    const size_t max_digits = max_size(*this, rhs);
    const int mag_cmp = compare_magnitude(*this, rhs);

    this->sign = POS;

    if (mag_cmp > 0) {

        for (size_t i = 0; i < max_digits; ++i) {
            if (i >= rhs.size())
                break;
            else {
                if (this->digits[i] < rhs.digits[i]) this->borrow(i);
                this->digits[i] = this->digits[i] - rhs.digits[i];
            }
        }
    }
    else if (mag_cmp < 0) {

        for (size_t i = 0; i < max_digits; ++i) {
            if (i >= this->size())
                this->digits.push_back(rhs.digits[i]);
            else {
                if (this->digits[i] > rhs.digits[i]) rhs.borrow(i);
                this->digits[i] = rhs.digits[i] - this->digits[i];
            }
        }

        this->sign = NEG;
    }
    else
        this->digits.push_back(0);

    this->remove_leading_zeros();
}

BigInt BigInt::sum(const BigInt& a, const BigInt& b)
{
    BigInt result(a);
    result.sum(b);
    return result;
}

BigInt BigInt::dif(BigInt a, BigInt b)
{
    BigInt result(a);
    result.dif(b);
    return result;
}

/**
 * @return The maximum digit count between the two parameters.
 */
size_t BigInt::max_size(const BigInt& a, const BigInt& b)
{
    return a.size() > b.size() ? a.size() : b.size();
}

/**
 *  @brief  Compares the magnitude of two BigInt types
 *  @retval  0 if a == b
 *           1 if a > b
 *          -1 if a < b
 */
int BigInt::compare_magnitude(const BigInt& a, const BigInt& b)
{
    int result = 0;

    if (a.size() > b.size())
        result = 1;
    
    else if (a.size() < b.size())
        result = -1;
    
    else {

        for (int i = a.size()-1; i >= 0; --i) {

            if (a.digits[i] > b.digits[i]) {
                result = 1;
                break;
            }
            else if (a.digits[i] < b.digits[i]) {
                result = -1;
                break;
            }
        }
    }

    return result;
}

