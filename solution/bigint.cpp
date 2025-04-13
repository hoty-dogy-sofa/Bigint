#include "bigint.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace pet_bigint {

bigint::bigint(const std::string& input) {
    const int power = static_cast<int>(log10(BASE));
    std::string parced_input = input;
    const size_t first_null = input.find_first_of("123456789");
    if (first_null != std::string::npos && first_null != 0) {
        parced_input = input.substr(first_null, input.length() - first_null);
    }
    int i = static_cast<int>(parced_input.length()) - power;
    while (i > 0) {
        digits_.push_back(stoi(parced_input.substr(i, power)));
        i -= power;
    }
    digits_.push_back(stoi(parced_input.substr(0, i + power)));
}

bigint::bigint(unsigned int input) : bigint(std::to_string(input)) {}

std::string bigint::to_string() const {
    std::stringstream Q;
    Q << digits_.back();
    Q << std::setw(static_cast<int>(log10(BASE))) << std::setfill('0');
    for (int i = static_cast<int>(digits_.size()) - 2; i >= 0; i--) {
        Q << digits_[i];
    }
    return Q.str();
}

bigint::operator unsigned int() const {
    std::stringstream Q;
    Q << to_string();
    unsigned int answer = 0;
    Q >> answer;
    return answer;
}

const bigint& bigint::operator+=(bigint second) {
    if (*this > second) {
        std::swap(*this, second);
    }
    int shift = 0;
    for (size_t i = 0; i < second.digits_.size(); i++) {
        if (i >= digits_.size()) {
            digits_.push_back(second.digits_[i] + shift);
            shift = (digits_.back() >= BASE ? 1 : 0);
            if (shift == 1) {
                digits_[i] = digits_[i] % BASE;
            }
        } else {
            digits_[i] += second.digits_[i] + shift;
            shift = (digits_[i] >= BASE ? 1 : 0);
            if (shift == 1) {
                digits_[i] = digits_[i] % BASE;
            }
        }
    }
    if (shift == 1) {
        digits_.push_back(1);
    }
    return *this;
}

const bigint& bigint::operator-=(const bigint& second) {
    int shift = 0;
    for (size_t i = 0; i < digits_.size(); i++) {
        if (i >= second.digits_.size()) {
            digits_[i] -= shift;
            if (digits_[i] < 0) {
                shift = 1;
                digits_[i] += BASE;
            } else {
                shift = 0;
            }
        } else {
            digits_[i] -= (second.digits_[i] + shift);
            if (digits_[i] < 0) {
                shift = 1;
                digits_[i] += BASE;
            } else {
                shift = 0;
            }
        }
    }
    while (digits_.back() == 0 && digits_.size() > 1) {
        digits_.pop_back();
    }
    return *this;
}

bool operator==(const bigint& first, const bigint& second) {
    if (first.digits_.size() != second.digits_.size()) {
        return false;
    }
    for (int i = static_cast<int>(first.digits_.size()) - 1; i >= 0; i--) {
        if (first.digits_[i] != second.digits_[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const bigint& first, const bigint& second) {
    return !(first == second);
}

bool operator<(const bigint& first, const bigint& second) {
    if (first.digits_.size() != second.digits_.size()) {
        return first.digits_.size() < second.digits_.size();
    }
    for (int i = static_cast<int>(first.digits_.size()) - 1; i >= 0; i--) {
        if (first.digits_[i] != second.digits_[i]) {
            return first.digits_[i] < second.digits_[i];
        }
    }
    return false;
}

bool operator>(const bigint& first, const bigint& second) {
    return !(first < second || first == second);
}

bool operator>=(const bigint& first, const bigint& second) {
    return !(first < second);
}

bool operator<=(const bigint& first, const bigint& second) {
    return !(first > second);
}

bigint& bigint::operator++() {
    *this += 1;
    return *this;
}

bigint& bigint::operator--() {
    *this -= 1;
    return *this;
}

bigint bigint::operator++(int) {
    bigint b = *this;
    ++(*this);
    return b;
}

bigint bigint::operator--(int) {
    bigint b = *this;
    --(*this);
    return b;
}

std::ostream& operator<<(std::ostream& os, const bigint& number) {
    return os << number.to_string();
}

std::istream& operator>>(std::istream& is, bigint& number) {
    std::string input;
    is >> input;
    number = bigint(input);
    return is;
}

bigint operator-(bigint first, const bigint& second) {
    first -= second;
    return first;
}

bigint operator+(bigint first, const bigint& second) {
    first += second;
    return first;
}

} // namespace pet_bigint
