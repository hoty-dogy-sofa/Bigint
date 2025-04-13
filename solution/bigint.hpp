#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <string>
#include <iosfwd>

namespace pet_bigint {

// NOLINTBEGIN
extern const int BASE;
// NOLINTEND

class bigint {
private:
    std::vector<int> digits_ = {};

public:
    explicit bigint(const std::string& input);
    bigint(unsigned int input = 0);
    
    [[nodiscard]] std::string to_string() const;
    explicit operator unsigned int() const;

    const bigint& operator+=(bigint second);
    const bigint& operator-=(const bigint& second);

    bigint& operator++();
    bigint& operator--();
    bigint operator++(int);
    bigint operator--(int);

    friend bool operator==(const bigint& first, const bigint& second);
    friend bool operator!=(const bigint& first, const bigint& second);
    friend bool operator<(const bigint& first, const bigint& second);
    friend bool operator>(const bigint& first, const bigint& second);
    friend bool operator>=(const bigint& first, const bigint& second);
    friend bool operator<=(const bigint& first, const bigint& second);

    friend std::ostream& operator<<(std::ostream& os, const bigint& number);
    friend std::istream& operator>>(std::istream& is, bigint& number);
};

bigint operator-(bigint first, const bigint& second);
bigint operator+(bigint first, const bigint& second);

} // namespace pet_bigint

#endif // BIGINT_HPP
