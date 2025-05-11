#include "long_number.hpp"
#include <cmath>
#include <string>

using ussr::LongNumber;
		
LongNumber::LongNumber() : numbers(nullptr), length(1), sign(0) {
    numbers = new int[length]{0};
}

LongNumber::LongNumber(const char* const str) {
	this->length = this->get_length(str);


	if (str[0] == '-')
	{
		sign = 1;
	}

	numbers = new int[length];
	int begin = 0;
	while (str[begin] == '0') begin++;
	if (length == 0) {
		sign = 0;
		length = 1;
		numbers = new int[length]{0};
	} else {
		for (int i = 0; i < length; i++)
		{
			numbers[i] = str[length + begin - i - 1 + sign] - '0';
		}
	}
}

LongNumber::LongNumber(const LongNumber& x) : length(x.length), sign(x.sign) {
    numbers = new int[length];
    std::copy(x.numbers, x.numbers + length, numbers);
}

LongNumber::LongNumber(LongNumber&& x) : numbers(x.numbers), length(x.length), sign(x.sign) {
    x.numbers = nullptr;
    x.length = 0;
    x.sign = 0;
}

LongNumber::~LongNumber() {
	delete[] numbers;
	numbers = nullptr;
	length = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	*this = LongNumber(str);
    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this != &x) {
        if (numbers) {
            delete[] numbers;
        }
        length = x.length;
        sign = x.sign;
        numbers = new int[length];
        std::copy(x.numbers, x.numbers + length, numbers);
    }
    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (numbers) {
		delete[] numbers;
	}
	numbers = x.numbers;
	length = x.length;
	sign = x.sign;
	x.numbers = nullptr;
	x.length = 0;
	x.sign = 0;

    return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (this->length != x.length || this->sign != x.sign) return 0;
	for (int i = 0; i < length; i++)
	{
		if (this->numbers[i] != x.numbers[i]) return 0;
	}

	return 1;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (this->sign != x.sign) return this->sign < x.sign;
	if (sign == 1) return -x > -(*this);
	if (this->length > x.length) return 1;
	if (this->length < x.length) return 0;

	for (int i = length - 1; i >= 0; i--)
	{
		if (this->numbers[i] > x.numbers[i]) return 1;
		if(this->numbers[i] < x.numbers[i]) return 0;
	}
	
	return 0;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return !(*this > x || *this == x);
}

LongNumber LongNumber::operator - () const {
	LongNumber result(*this);
	if (result != LongNumber("0")) {
		result.sign = !sign;
	}
	return result;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	if (this->sign == x.sign){
		int max_length = std::max(this->length, x.length) + 1;
		char* buffer = new char[max_length]();
		int cf = 0;

		for (int i = 0; i < max_length - 1; i++) {
			int sum = cf;
			if (i < this->length) {
				sum += this->numbers[i];
			}
			if (i < x.length) {
				sum += x.numbers[i];
			}
			buffer[i] = sum % 10;
			cf = sum / 10;
		}

		if (cf > 0) {
			buffer[max_length - 1] = cf;
		} else {
			max_length--;
		}

		char* res = new char[max_length + 1];
		for (int i = 0; i < max_length; i++) {
			res[i] = buffer[max_length - i - 1] + '0';
		}
		res[max_length] = '\0';

		LongNumber ans{res};
		ans.sign = x.sign;
		delete[] buffer;
		delete[] res;
		return ans;
	}
	return *this - (-x);
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	if (sign != x.sign) {
        return *this + (-x);
    }
    
    if (sign == 1) {
        return (-x) - (-*this);
    }
    
    bool this_larger = true;
    if (length != x.length) {
        this_larger = length > x.length;
    } else {
        for (int i = length-1; i >= 0; i--) {
            if (numbers[i] != x.numbers[i]) {
                this_larger = numbers[i] > x.numbers[i];
                break;
            }
        }
    }
    
    if (!this_larger) {
        return -(x - *this);
    }
    
    LongNumber result;
    result.sign = 0;
    result.numbers = new int[length]{};
    result.length = length;
    
    int borrow = 0;
    for (int i = 0; i < length; i++) {
        int a = numbers[i];
        int b = i < x.length ? x.numbers[i] : 0;
        int diff = a - b - borrow;
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.numbers[i] = diff;
    }
    
    while (result.length > 1 && result.numbers[result.length-1] == 0) {
        result.length--;
    }
    
    return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	int max_buffer_length = this->length + x.length;
	int* buffer = new int[max_buffer_length]();
	int result_length = 0;

	int sign = this->sign ^ x.sign;

	for (int i = 0; i < this->length; i++) {
		for (int j = 0; j < x.length; j++) {
			buffer[i + j] += this->numbers[i] * x.numbers[j];
			result_length = i + j + 1;
			if (buffer[i + j] >= 10) {
				buffer[i + j + 1] += buffer[i + j] / 10;
				buffer[i + j] %= 10;
				++result_length;
			}
		}
	}

	if (sign) {
		result_length++;
	}
	char* res = new char[result_length + 1];
	if (sign) {
		res[0] = '-';
		for (int i = 1; i < result_length; i++) {
			res[i] = buffer[result_length - 1 - i] + '0';
		}
	} else {
		for (int i = 0; i < result_length; i++) {
			res[i] = buffer[result_length - 1 - i] + '0';
		}
	} 
	res[result_length] = '\0';

	LongNumber ans{res};
	delete[] buffer;
	delete[] res;
	return ans;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	if (x == LongNumber("0")) throw std::invalid_argument("Division by zero");

	LongNumber dividend(*this);
    dividend.sign = 0;
    LongNumber divisor(x);
    divisor.sign = 0;
	if (divisor > dividend) return LongNumber("0");

	LongNumber res;
    res.sign = sign ^ x.sign;
    res.length = length;
    res.numbers = new int[res.length]{};
    
    LongNumber current;
    for (int i = length - 1; i >= 0; i--) {
        current = current * LongNumber("10") + LongNumber(std::to_string(numbers[i]).c_str());
        
        int digit = 0;
        while (current > divisor || current == divisor) {
            current = current - divisor;
			digit++;
        }

		res.numbers[i] = digit;
    }

    while (res.length > 1 && res.numbers[res.length-1] == 0) {
        res.length--;
    }

	if (sign && ((*this) % x != LongNumber("0"))) {
		if (res.sign) res = res - LongNumber("1");
		else res = res + LongNumber("1");
	}
    
    return res;
}
LongNumber LongNumber::operator % (const LongNumber& x) const {
	if (x == LongNumber("0")) throw std::invalid_argument("Division by zero");

	LongNumber dividend = *this;
    dividend.sign = 0;
    LongNumber abs_divisor = x;
    abs_divisor.sign = 0;
    LongNumber res;
    for (int i = dividend.length - 1; i >= 0; i--) {
        res = res * LongNumber("10") + LongNumber(std::to_string(dividend.numbers[i]).c_str());
        while (res > abs_divisor || res == abs_divisor) {
            res = res - abs_divisor;
        }
    }

    if (this->is_negative() && res != LongNumber("0")) {
        res = abs_divisor - res;
    }
    
    return res;
}

int LongNumber::get_digits_number() const noexcept {
	return (length);
}

int LongNumber::get_rank_number(int rank) const {
	return (numbers[length - rank]);
}

bool LongNumber::is_negative() const noexcept {
	return (this->sign);
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int length = 0;
	int begin = 0;
	while (str[begin] == '0' || str[begin] == '-') begin++;
	while (str[length + begin] != '\0') length++;
	return length;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace ussr {
	std::ostream& operator << (std::ostream &os, const LongNumber& x)
	{
		if (x.sign)
		{
			os << '-';
		}
		for (int i = x.length - 1; i > -1; i--)
		{
			os << x.numbers[i];
		}
		return os;
	}
}
