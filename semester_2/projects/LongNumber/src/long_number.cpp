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
        length--;
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
        // if zero 
        if (str[0] == '0' && str[1] == '\0') {
            length = 1;
            sign = 1;
            numbers = new int[length];
            numbers[0] = 0;
            return *this;
        }
        
        length = strlen(str);
        if (str[0] == '-') {
            sign = -1;
            length--;
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

        return *this;
    
}

LongNumber& LongNumber::operator = (const LongNumber& x ){
            delete[] numbers;
            length = x.length;
            sign = x.sign;
            numbers = new int[length];
            for (int i = 0; i < length; i++) {
                numbers[i] = x.numbers[i];
            }
    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
            length = x.length;
            sign = x.sign;
            numbers = x.numbers;
            x.numbers = nullptr;
            return *this;
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
    for (int i = length-1; i >= 0; --i) {
        // cout<<"n:1 "<<numbers[i]<<" num2: "<< x.numbers[i]<<endl;
        if (numbers[i] != x.numbers[i]) {
            return (sign == 1) ? (numbers[i] > x.numbers[i]) : (numbers[i] < x.numbers[i]);
        }
    }
    return false;

}

bool LongNumber::operator < (const LongNumber& x) const {
    bool isgreater = *this > x;
    bool isequal = *this == x;
    // cout<<"this: "<<*this<<"    x: "<< x<<endl;
    // cout<<"is greater: "<<isgreater<<endl;
    // cout<<"is equal: "<< isequal<<endl<<endl<<endl;
    return !(isgreater || isequal);
}

bool LongNumber::operator >= (const LongNumber& x) const {
    return !(*this < x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    LongNumber result;

    if (sign == x.sign) {
        result.length = max(length, x.length) + 1;
        result.numbers = new int[result.length];
        int carry = 0;
        for (int i = 0; i < result.length; ++i) {
            int sum = (i < length ? numbers[i] : 0) +
                      (i < x.length ? x.numbers[i] : 0) +
                      carry;
            result.numbers[i] = sum % 10;
            carry = sum / 10;
        }
        result.sign = sign;
                    
        // Remove leading zeros
        while (result.length > 1 && result.numbers[result.length - 1] == 0) {
            result.length--;
        }

        return result;
    }
    else {
        LongNumber positive, negative, reduced, substructed;
        if (*this > x) {
            positive = *this;
            negative = x;
        } else {
            positive = x;
            negative = *this;
        }
        
        negative.sign = 1;

        if (positive > negative) {
            reduced = positive;
            substructed = negative;
            result.sign = 1;
        } else {
            reduced = negative;
            substructed = positive;
            result.sign = -1;
        }

        result.length = reduced.length;
        result.numbers = new int[result.length];
        
        int borrow = 0;
        for (int i = 0; i < result.length || borrow; ++i) {
            int diff = reduced.numbers[i] - borrow - ((i < substructed.length) ? substructed.numbers[i] : 0);
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

        if (result.length == 1 && result.numbers[0] == 0) {
            result.sign = 1;
        }
        return result;
    }
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    LongNumber redused = *this;
    LongNumber substructed = x;
    substructed.sign *=-1;

    return redused + substructed;

}

LongNumber LongNumber::operator * (const LongNumber& x) const {
    LongNumber result;
    result.length = length + x.length;
    result.numbers = new int[result.length]{0};

    for (int i = 0; i < length; ++i) {
        int carry = 0;
        for (int j = 0; j < x.length || carry; ++j) {
            long long current = result.numbers[i + j] +
                numbers[i] * (j < x.length ? x.numbers[j] : 0) + carry;
            result.numbers[i + j] = current % 10;
            carry = current / 10;
        }
    }

    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }

    result.sign = (sign == x.sign) ? 1 : -1;
    return result;
}

LongNumber LongNumber::operator/(const LongNumber& x) const {
    LongNumber result;
    result.length = length;
    result.numbers = new int[result.length];
    result.sign = (sign == x.sign) ? 1 : -1;

    LongNumber dividend = *this;
    dividend.sign = 1;
    LongNumber divisor = x;
    divisor.sign = 1;

    if (dividend < divisor) {
        result = "0";
        return result;
    }

    // cout<<"\n dividend: "<<dividend<<" divisor: "<<divisor<<endl;

    LongNumber current("0");
    LongNumber ten("10");
    for (int i = dividend.length - 1; i >= 0; --i) {

        current = (current * ten) + LongNumber(to_string(dividend.numbers[i]).c_str());
        // cout<<"current: "<<current<<" divisor: "<<divisor<<endl;
        int digit = 0;
        while (current >= divisor) {
            current = (current - divisor);
            // cout<<"reduced current: "<<current<<endl;
            ++digit;
        }
        // cout<<"digit: "<<digit<<endl;
        result.numbers[i] = digit;
    }

    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        --result.length;
    }

    // cout<<"result: "<<result<<endl<<endl<<endl;
    return result;

}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber copy = *this;
    LongNumber copyx = x;
    LongNumber integer_part, quotient, result;
    if (sign == 1 && x.sign == 1){
        integer_part = copy / x;
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }else if (sign == -1 && x.sign == 1){
        integer_part = (copy / x) - LongNumber("1");
        // cout<<"\ninteger part: "<<integer_part<<endl;
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }else if(sign == 1 && x.sign == -1){
        integer_part = copy / x;
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }else{
        integer_part = (copy / x) + LongNumber("1");
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }

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