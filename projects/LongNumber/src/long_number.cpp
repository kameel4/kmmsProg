#include "long_number.hpp"

using biv::LongNumber;
		
LongNumber::LongNumber() {
	length = 0;
    sign = 1;
    numbers = nullptr;
}

LongNumber::LongNumber(const char* const str) {
    length = strlen(str);
    
    if (str[0] == '-') {
        sign = -1;
    }else{
        sign = 1;
    }

    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = (str[i + (sign == -1)] - '0');
    }
    
    for (int i = 0; i < length / 2; ++i) {
        swap(numbers[i], numbers[length - i - 1]);
    }


}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
    sign = x.sign;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& x) {
    length = x.length;
    sign = x.sign;
    numbers = x.numbers;
}

LongNumber::~LongNumber() {
    delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
        delete[] numbers;
        length = get_length(str);
        if (str[0] == '-') {
            sign = -1;
        }else{
            sign = 1;
        }
        numbers = new int[length];
        for (int i = 0; i < length; i++) {
            numbers[i] = (str[i + (sign == -1)] - '0');
        }
    
}

LongNumber& LongNumber::operator = (const LongNumber& x ){
            delete[] numbers;
            length = x.length;
            sign = x.sign;
            numbers = new int[length];
            for (int i = 0; i < length; i++) {
                numbers[i] = x.numbers[i];
            }
    
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
            length = x.length;
            sign = x.sign;
            numbers = x.numbers;
            x.numbers = nullptr;
}

bool LongNumber::operator == (const LongNumber& x) const {
            if (length != x.length || sign != x.sign) {
                return false;
            }
            for (int i = 0; i < length; i++) {
                if (numbers[i] != x.numbers[i]) {
                    return false;
                }
            }
            return true;
		
    
}

bool LongNumber::operator != (const LongNumber& x) const {
            return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
    if (sign != x.sign) {
        return sign > x.sign;
    }
    if (length != x.length) {
        return (sign == 1) ? (length > x.length) : (length < x.length);
    }
    for (int i = 0; i < length; ++i) {
        if (numbers[i] != x.numbers[i]) {
            return (sign == 1) ? (numbers[i] > x.numbers[i]) : (numbers[i] < x.numbers[i]);
        }
    }
    return false;

}

bool LongNumber::operator < (const LongNumber& x) const {
    return !(*this > x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    LongNumber result;
    result.length = max(length, x.length);
    result.numbers = new int[result.length];
    int carry = 0;
    for (int i = 0; i < result.length; ++i) {
        int sum = (i < length ? numbers[i] : 0) +
                  (i < x.length ? x.numbers[i] : 0) +
                  carry;
        result.numbers[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        ++result.length;
        result.numbers[result.length - 1] = carry;
    }
    result.sign = (sign == x.sign ? sign : 1);
    return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    LongNumber result;
    if (*this == x) {
        result = LongNumber("0");
        return result;
    }

    // Assuming `*this` is larger than `x` for subtraction
    result.length = max(length, x.length);
    result.numbers = new int[result.length];
    int borrow = 0;
    for (int i = 0; i < result.length; ++i) {
        int diff = (i < length ? numbers[i] : 0) -
                   (i < x.length ? x.numbers[i] : 0) -
                   borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.numbers[i] = diff;
    }

    // Remove leading zeros
    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }

    result.sign = (sign == x.sign) ? sign : 1;
    return result;

}

LongNumber LongNumber::operator * (const LongNumber& x) const {
    LongNumber result;
    result.length = length + x.length;
    result.numbers = new int[result.length]{0};
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < x.length; ++j) {
            result.numbers[i + j] += numbers[i] * x.numbers[j];
        }
    }
    for (int i = 0; i < result.length - 1; ++i) {
        result.numbers[i + 1] += result.numbers[i] / 10;
        result.numbers[i] %= 10;
    }
    // Remove leading zeros
    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }
    result.sign = (sign == x.sign ? 1 : -1);
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    if (x == 0) {
        throw overflow_error("Division by zero");
    }

    LongNumber result;
    result.length = length;
    result.numbers = new int[result.length];
    int remainder = 0;
    for (int i = length - 1; i >= 0; --i) {
        int dividend = remainder * 10 + numbers[i];
        result.numbers[i] = dividend / x.numbers[0];
        remainder = dividend % x.numbers[0];
    }
    
    
    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }
    result.sign = (sign == x.sign ? 1 : -1);
    return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber result = *this - (*this / x) * x;
    return result;
}

int LongNumber::get_digits_number() const noexcept {
    return length;
}

int LongNumber::get_rank_number(int rank) const {
    if (rank < 1 || rank > length) {
        throw out_of_range("Specified rank is out of range");
    }
    return numbers[length - rank];
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
    return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv {
	ostream& operator << (ostream &os, const LongNumber& x) {
		if (x.sign == -1) {
			os << '-';
		}
		for (int i = x.length - 1; i >= 0; --i) {
			os << x.numbers[i];
		}
		return os;
	}
}